//
// WebServerDispatcher.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerDispatcher
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/Web/MediaTypeMapper.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Delegate.h"
#include "Poco/URI.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"
#include "Poco/ScopedLock.h"
#include "Poco/File.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DeflatingStream.h"
#include "Poco/MemoryStream.h"
#include "Poco/Message.h"
#include <memory>
#include <limits>


using Poco::OSP::Auth::AuthService;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPBasicCredentials;
using Poco::Delegate;
using Poco::Path;
using Poco::StreamCopier;
using Poco::FastMutex;


namespace Poco {
namespace OSP {
namespace Web {


const std::string WebServerDispatcher::SERVICE_NAME("osp.web.dispatcher");


WebServerDispatcher::WebServerDispatcher(BundleContext::Ptr pContext, MediaTypeMapper::Ptr pMediaTypeMapper, const std::string& authServiceName, bool compressResponses, const std::set<std::string>& compressedMediaTypes, bool cacheResources):
	_pContext(pContext),
	_pMediaTypeMapper(pMediaTypeMapper),
	_authServiceName(authServiceName),
	_compressResponses(compressResponses),
	_compressedMediaTypes(compressedMediaTypes),
	_cacheResources(cacheResources),
	_threadPool("WebServer"),
	_accessLogger(Poco::Logger::get("osp.web.access"))
{
	_pContext->events().bundleStopping += Delegate<WebServerDispatcher, BundleEvent>(this, &WebServerDispatcher::onBundleStopping);
}


WebServerDispatcher::~WebServerDispatcher()
{
	try
	{
		_pContext->events().bundleStopping -= Delegate<WebServerDispatcher, BundleEvent>(this, &WebServerDispatcher::onBundleStopping);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


const std::type_info& WebServerDispatcher::type() const
{
	return typeid(WebServerDispatcher);
}


bool WebServerDispatcher::isA(const std::type_info& otherType) const
{
	std::string name(typeid(WebServerDispatcher).name());
	return name == otherType.name() || Service::isA(otherType);
}


void WebServerDispatcher::addVirtualPath(const VirtualPath& virtualPath)
{
	FastMutex::ScopedLock lock(_mutex);

	if (virtualPath.pPattern)
	{
		_patternVec.push_back(virtualPath);

		std::string msg("Pattern '");
		msg += virtualPath.path;
		msg += "' mapped by bundle ";
		msg += virtualPath.pOwnerBundle->symbolicName();
		msg += " to request handler.";
		_pContext->logger().information(msg);
	}
	else
	{
		VirtualPath vPath(virtualPath);
		vPath.path = normalizePath(vPath.path);
		Poco::Path path(vPath.path);
		PathMap::iterator itTmp;
	
		// we have to check if a parent entry exists, start with /
		std::string entry("/");
		PathMap::const_iterator it = _pathMap.find(entry);
		if (it != _pathMap.end())
		{
			if (it->second.security.mode < vPath.security.mode || vPath.path == entry || it->second.security.mode == SM_NONE ||
				(it->second.security.mode == SM_OWNER && vPath.pOwnerBundle != it->second.pOwnerBundle))
				throw Poco::InvalidArgumentException("A protected path mapping (" + it->second.path + ") already exists for that virtual path: " + vPath.path);
		}
		int depth = path.depth();
		for (int i = 0; i < depth; ++i)
		{
			entry += path[i];
			entry += '/';
			it = _pathMap.find(entry);
			if (it != _pathMap.end())
			{
				if (it->second.security.mode < vPath.security.mode || vPath.path == entry || it->second.security.mode == SM_NONE ||
					(it->second.security.mode == SM_OWNER && vPath.pOwnerBundle != it->second.pOwnerBundle))
					throw Poco::InvalidArgumentException("A protected path mapping (" + it->second.path + ") already exists for that virtual path: " + vPath.path);
			}
		}
		poco_assert_dbg (entry == vPath.path);
		// temporary insert the mapping
		itTmp = _pathMap.insert(std::make_pair(vPath.path, vPath)).first;

		it = itTmp;
		++it;
		// we also have to check that no children exist that would violate the specializationMode
		while (it != _pathMap.end() && itTmp->first == it->first.substr(0, vPath.path.size()))
		{
			// search for a child that has a less stricter mode than the parent or that has mode none
			// or search for a child that has mode SM_OWNER and a different owner
			if (it->second.security.mode > vPath.security.mode || vPath.security.mode == SM_NONE ||
				(vPath.security.mode == SM_OWNER && vPath.pOwnerBundle != it->second.pOwnerBundle))
			{
				_pathMap.erase(itTmp);
				throw Poco::PathSyntaxException("A protected child mapping (" + it->second.path + ") already exists for that virtual path: " + vPath.path);
			}
			++it;
		}
	
		std::string msg("Virtual path '");
		msg += vPath.path;
		msg += "' mapped by bundle ";
		msg += vPath.pOwnerBundle->symbolicName();
		msg += " to ";
		if (!vPath.resource.empty())
		{
			msg += "resource path '";
			msg += vPath.resource;
			msg += "'";
		}
		else msg += "request handler";
		msg += ".";
		_pContext->logger().information(msg);
	}
}


void WebServerDispatcher::removeVirtualPath(const std::string& virtualPath)
{
	FastMutex::ScopedLock lock(_mutex);

	std::string vPath(normalizePath(virtualPath));
	if (_pathMap.erase(vPath) == 0)
	{
		for (PatternVec::iterator it = _patternVec.begin(); it != _patternVec.end();)
		{
			if (it->path == virtualPath)
			{
				it = _patternVec.erase(it);
				break;
			}
			else
			{
				++it;
			}
		}
	}
	std::string msg("Virtual path '");
	msg += vPath;
	msg += "' unmapped.";
	_pContext->logger().information(msg);
}


void WebServerDispatcher::listVirtualPaths(PathInfoMap& paths) const
{
	FastMutex::ScopedLock lock(_mutex);
	
	paths.clear();
	for (PathMap::const_iterator it = _pathMap.begin(); it != _pathMap.end(); ++it)
	{
		if (!it->second.hidden)
		{
			PathInfo info;
			info.description = it->second.description;
			info.permission  = it->second.security.permission;
			info.session     = it->second.security.session;
			info.pBundle     = it->second.pOwnerBundle;
			paths[it->first] = info;
		}
	}
}


void WebServerDispatcher::virtualPathMappings(PathMap& mappings) const
{
	FastMutex::ScopedLock lock(_mutex);

	mappings = _pathMap;
}


void WebServerDispatcher::addFilter(const std::string& mediaType, WebFilterFactoryPtr pFilterFactory, const WebFilter::Args& args)
{
	Poco::FastMutex::ScopedLock lock(_filterFactoryMutex);
	
	FilterFactoryMap::iterator it = _filterFactoryMap.find(mediaType);
	if (it == _filterFactoryMap.end())
	{
		_filterFactoryMap[mediaType].pFactory = pFilterFactory;
		_filterFactoryMap[mediaType].args = args;
	}
	else throw Poco::ExistsException("WebFilter", mediaType);
}


void WebServerDispatcher::removeFilter(const std::string& mediaType)
{
	Poco::FastMutex::ScopedLock lock(_filterFactoryMutex);

	_filterFactoryMap.erase(mediaType);
}


void WebServerDispatcher::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, bool secure)
{
	std::string username;
	try
	{
		URI uri(request.getURI());
		std::string path(uri.getPath());
		if (cleanPath(path))
		{
			Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);
			const VirtualPath& vPath = mapPath(path, request.getMethod());
			if (vPath.security.secure && !secure)
			{
				std::string vpath(vPath.path);
				lock.unlock();
				sendResponse(request, HTTPResponse::HTTP_FORBIDDEN, formatMessage("secure", vpath));
			}
			else if (authorize(request, vPath, username))
			{
				if (vPath.pFactory)
				{
					if (vPath.methods.empty() || vPath.methods.count(request.getMethod()) == 1)
					{
						RequestHandlerFactoryPtr pFactory(vPath.pFactory);
						lock.unlock();
#if __cplusplus < 201103L
						std::auto_ptr<HTTPRequestHandler> pHandler(pFactory->createRequestHandler(request));
#else
						std::unique_ptr<HTTPRequestHandler> pHandler(pFactory->createRequestHandler(request));
#endif
						try
						{
							if (pHandler.get())
								pHandler->handleRequest(request, response);
							else
								sendNotFound(request, path);
						}
						catch (Poco::Exception& exc)
						{
							throw Poco::UnhandledException("Request Handler", exc.displayText());
						}
					}
					else
					{
						sendMethodNotAllowed(request, formatMessage("method", request.getMethod(), request.getURI()));
					}
				}
				else
				{
					if (path.size() >= vPath.path.size())
					{
						std::string vpath(vPath.path);
						std::string resPath(path, vPath.path.size(), std::string::npos);
						std::string resBase(vPath.resource);
						std::string index(vPath.indexPage);
						if (index.empty()) index = "index.html";
						Bundle::ConstPtr pBundle(vPath.pOwnerBundle);
						bool canCache = vPath.cache;
						lock.unlock();
						sendResource(request, path, vpath, resPath, resBase, index, pBundle, canCache);
					}
					else
					{
						std::string newPath(vPath.path);
						lock.unlock();
						sendFound(request, newPath);
					}
				}
			}
			else
			{
				if (vPath.security.session.empty())
				{
					if (vPath.security.realm.empty())
						response.requireAuthentication(vPath.path);
					else
						response.requireAuthentication(vPath.security.realm);
				}
				std::string vpath(vPath.path);
				lock.unlock();
				sendNotAuthorized(request, vpath);
			}
		}
		else
		{
			sendBadRequest(request, formatMessage("invalid"));
		}
	}
	catch (Poco::NotFoundException&)
	{
		try
		{
			sendNotFound(request, request.getURI());
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().log(exc);
		}
	}	
	catch (Poco::Exception& exc)
	{
		try
		{
			std::string msg("Error processing ");
			msg += request.getMethod();
			msg += " request for \"";
			msg += request.getURI();
			msg += "\" from ";
			msg += request.clientAddress().toString();
			msg += ": ";
			msg += exc.displayText();
			_pContext->logger().error(msg);
			sendInternalError(request, exc.displayText());
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().log(exc);
		}
	}
	
	// clear out any remaining data in request body
	if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST || request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT)
	{
		if (Poco::icompare(request.get(Poco::Net::HTTPMessage::CONNECTION, ""), Poco::Net::HTTPRequest::UPGRADE) != 0)
		{ 
			request.stream().ignore(std::numeric_limits<std::streamsize>::max()); 
		}
	}

	if (_accessLogger.information())
	{
		logRequest(request, response, username);
	}
}


void WebServerDispatcher::logRequest(const Poco::Net::HTTPServerRequest& request, const Poco::Net::HTTPServerResponse& response, const std::string& username)
{
	std::string reqText(request.getMethod());
	reqText += ' ';
	reqText += request.getURI();
	reqText += ' ';
	reqText += request.getVersion();
	
	Poco::Message message(_accessLogger.name(), reqText, Poco::Message::PRIO_INFORMATION);
	
	if (username.empty())
		message["username"] = "-";
	else
		message["username"] = username;
		
	message["status"] = Poco::NumberFormatter::format(static_cast<int>(response.getStatus()));
	message["client"] = request.clientAddress().host().toString();
	
	if (response.getContentLength64() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		message["size"] = Poco::NumberFormatter::format(response.getContentLength64());
	else
		message["size"] = "-";
		
	message["referer"] = request.get("Referer", "");
	message["useragent"] = request.get("User-Agent", "");
	
	_accessLogger.log(message);
}


void WebServerDispatcher::sendResource(Poco::Net::HTTPServerRequest& request, const std::string& path, const std::string& vpath, const std::string& resPath, const std::string& resBase, const std::string& index, Bundle::ConstPtr pBundle, bool canCache)
{
	const std::string& meth(request.getMethod());
	Poco::Net::HTTPServerResponse& response(request.response());
	std::string mediaType;
	std::string resolvedPath;
#if __cplusplus < 201103L
	std::auto_ptr<std::istream> pResourceStream(findResource(pBundle, resBase, resPath, index, mediaType, resolvedPath, canCache));
#else
	std::unique_ptr<std::istream> pResourceStream(findResource(pBundle, resBase, resPath, index, mediaType, resolvedPath, canCache));
#endif
	if (pResourceStream.get())
	{
		response.setContentType(mediaType);
		
		Poco::SharedPtr<WebFilter> pFilter = findFilter(mediaType);
		if (pFilter)
		{
			response.setChunkedTransferEncoding(true);
			pFilter->process(request, response, resolvedPath, *pResourceStream, pBundle);
		}
		else if (meth == "GET" || meth == "HEAD")
		{
			Poco::File bundleFile(pBundle->path());
			Poco::Timestamp lastModified = bundleFile.getLastModified();
			response.set("Last-Modified", DateTimeFormatter::format(lastModified, DateTimeFormat::HTTP_FORMAT));
			if (request.has("If-Modified-Since"))
			{
				Poco::DateTime modifiedSince;
				int tzd;
				Poco::DateTimeParser::parse(request.get("If-Modified-Since"), modifiedSince, tzd);
				if (lastModified <= modifiedSince.timestamp())
				{
					response.setContentLength(0);
					response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_MODIFIED);
					response.send();
					return;
				}
			}
	
			response.setChunkedTransferEncoding(true);
			bool compressResponse(_compressResponses && request.hasToken("Accept-Encoding", "gzip") && shouldCompressMediaType(mediaType));
			if (compressResponse) response.set("Content-Encoding", "gzip");

			std::ostream& responseStream = response.send();
			if (meth == "GET")
			{
				if (compressResponse)
				{
					Poco::DeflatingOutputStream gzipStream(responseStream, Poco::DeflatingStreamBuf::STREAM_GZIP, 1);
					StreamCopier::copyStream(*pResourceStream, gzipStream);
				}
				else
				{
					StreamCopier::copyStream(*pResourceStream, responseStream);
				}
			}
		}
		else
		{
			sendMethodNotAllowed(request, formatMessage("method", meth, request.getURI()));
		}
	}
	else if (path.size() == vpath.size())
	{
		sendForbidden(request, path);
	}
	else
	{
		sendNotFound(request, path);
	}
}


WebServerDispatcher::WebFilterPtr WebServerDispatcher::findFilter(const std::string& mediaType)
{
	WebFilterPtr pFilter;
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_filterFactoryMutex);
	FilterFactoryMap::iterator it = _filterFactoryMap.find(mediaType);
	if (it != _filterFactoryMap.end())
	{
		WebFilterFactoryInfo factoryInfo = it->second;
		lock.unlock();
		pFilter = factoryInfo.pFactory->createFilter(factoryInfo.args);
	}
	return pFilter;
}


void WebServerDispatcher::removeBundle(Bundle::ConstPtr pBundle)
{
	FastMutex::ScopedLock lock(_mutex);

	PathMap::iterator itm = _pathMap.begin();
	while (itm != _pathMap.end())
	{
		if (itm->second.pOwnerBundle == pBundle)
		{
			std::string path(itm->first);
			PathMap::iterator delIt(itm);
			++itm;
			_pathMap.erase(delIt);
			std::string msg("Virtual path '");
			msg += path;
			msg += "' unmapped because its bundle (";
			msg += pBundle->symbolicName();
			msg += ") is stopping.";
			_pContext->logger().information(msg);
		}
		else ++itm;
	}
	
	PatternVec::iterator itv = _patternVec.begin();
	while (itv != _patternVec.end())
	{
		if (itv->pOwnerBundle == pBundle)
		{
			std::string pattern(itv->path);
			itv = _patternVec.erase(itv);
			std::string msg("Pattern '");
			msg += pattern;
			msg += "' unmapped because its bundle (";
			msg += pBundle->symbolicName();
			msg += ") is stopping.";
			_pContext->logger().information(msg);
		}
		else
		{
			++itv;
		}
	}
}


void WebServerDispatcher::uncacheBundleResources(Bundle::ConstPtr pBundle)
{
	std::string cachePath = "//";
	cachePath += pBundle->symbolicName();
	cachePath += "/";
	
	Poco::FastMutex::ScopedLock lock(_resourceCacheMutex);

	ResourceCache::iterator it = _resourceCache.begin();
	ResourceCache::iterator end = _resourceCache.end();
	while (it != end)
	{
		if (it->first.compare(0, cachePath.size(), cachePath) == 0)
		{
			ResourceCache::iterator itDel = it;
			++it;
			_resourceCache.erase(itDel);
		}
		else ++it;
	}
}


void WebServerDispatcher::onBundleStopping(const void*, BundleEvent& ev)
{
	Bundle::ConstPtr pBundle = ev.bundle();
	removeBundle(pBundle);
	uncacheBundleResources(pBundle);
}


std::string WebServerDispatcher::normalizePath(const std::string& path)
{
	if (!path.empty())
	{
		std::string absPath("/");
		if (path[0] != '/')
			absPath += path;
		else
			absPath = path;
		if (absPath != "/")
		{
			Poco::Path p(absPath, Poco::Path::PATH_UNIX);
			p.makeDirectory();
			return p.toString(Poco::Path::PATH_UNIX);
		}
	}
	return "/";
}


const WebServerDispatcher::VirtualPath& WebServerDispatcher::mapPath(const std::string& path, const std::string& method) const
{
	PatternVec::const_iterator foundItv = _patternVec.end();
	for (PatternVec::const_iterator itv = _patternVec.begin(); itv != _patternVec.end(); ++itv)
	{
		if (itv->pPattern->match(path))
		{
			if (foundItv == _patternVec.end())
			{
				// Return something matching the pattern even if methods don't match.
				// Methods will be checked by caller, so a proper 405 can be returned.
				foundItv = itv;
			}
			else
			{
				// Already have something, but this also matches method.
				if (itv->methods.empty() || itv->methods.count(method) == 1)
					foundItv = itv;
			}
		}
	}
	if (foundItv != _patternVec.end())
	{
		return *foundItv;
	}
	else
	{
		std::string normPath(normalizePath(path));
		Path p(normPath, Path::PATH_UNIX);
		std::string parent("/");
		PathMap::const_iterator foundIt = _pathMap.find(parent);
		for (int i = 0; i < p.depth(); ++i)
		{
			parent += p[i];
			parent += '/';
			PathMap::const_iterator it = _pathMap.find(parent);
			if (it != _pathMap.end() && !it->second.pPattern)
				foundIt = it;
		}
		if (foundIt != _pathMap.end())
		{
			return foundIt->second;
		}
		else throw Poco::NotFoundException(path);
	}
}


std::istream* WebServerDispatcher::findResource(Bundle::ConstPtr pBundle, const std::string& base, const std::string& res, const std::string& index, std::string& mediaType, std::string& resolvedPath, bool canCache) const
{
	Path basePath(base, Path::PATH_UNIX);
	basePath.makeDirectory();
	Path resPath(res, Path::PATH_UNIX);
	basePath.append(resPath);
	resolvedPath = basePath.toString(Path::PATH_UNIX);
	mediaType = _pMediaTypeMapper->map(basePath.getExtension());
	std::istream* pStream = getCachedResource(pBundle, resolvedPath, canCache);
	if (!pStream)
	{
		basePath.makeDirectory();
		basePath.setFileName(index);
		resolvedPath = basePath.toString(Path::PATH_UNIX);
		mediaType = _pMediaTypeMapper->map(basePath.getExtension());
		pStream = getCachedResource(pBundle, resolvedPath, canCache);
	}
	return pStream;
}


std::istream* WebServerDispatcher::getCachedResource(Bundle::ConstPtr pBundle, const std::string& path, bool canCache) const
{
	if (_cacheResources && canCache)
	{
		std::string cachePath = "//";
		cachePath += pBundle->symbolicName();
		cachePath += "/";
		cachePath += path;
		Poco::ScopedLockWithUnlock<Poco::FastMutex> lockWithUnlock(_resourceCacheMutex);
		ResourceCache::iterator it = _resourceCache.find(cachePath);
		if (it != _resourceCache.end())
		{
			return new Poco::MemoryInputStream(it->second.data(), it->second.size());
		}
		else
		{
			lockWithUnlock.unlock();
#if __cplusplus < 201103L
			std::auto_ptr<std::istream> pResourceStream(pBundle->getResource(path));
#else
			std::unique_ptr<std::istream> pResourceStream(pBundle->getResource(path));
#endif
			if (pResourceStream.get())
			{
				std::string cachedData;
				Poco::StreamCopier::copyToString(*pResourceStream, cachedData);

				Poco::FastMutex::ScopedLock lock(_resourceCacheMutex);
				// Make sure another thread has not cached the resource in the meantime.
				it = _resourceCache.find(cachePath);
				if (it == _resourceCache.end())
				{
					std::string& cacheEntry = _resourceCache[cachePath];
					std::swap(cachedData, cacheEntry);
					return new Poco::MemoryInputStream(cacheEntry.data(), cacheEntry.size());
				}
				else
				{
					return new Poco::MemoryInputStream(it->second.data(), it->second.size());
				}
			}
			else return 0;
		}
	}
	else
	{
		_pContext->logger().debug("Cannot cache: " + path);
		return pBundle->getResource(path);
	}
}


bool WebServerDispatcher::cleanPath(std::string& path)
{
	std::string::iterator it(path.begin());
	std::string::iterator end(path.end());
	for (; it != end; ++it)
	{
		if (*it == '\\')
			*it = '/';
	}
	while (path.size() > 0 && path[path.size() - 1] == '.')
		path.resize(path.size() - 1);
	
	if (path.size() > 0)
	{
		Path p(path, Path::PATH_UNIX);
		p.makeDirectory();
		for (int i = 0; i < p.depth(); ++i)
		{
			if (p[i] == "." || p[i] == "..")
				return false;
		}
		return true;
	}
	else return false;
}


bool WebServerDispatcher::authorize(Poco::Net::HTTPServerRequest& request, const VirtualPath& vPath, std::string& username) const
{
	if (vPath.security.permission.empty())
	{
		return true;
	}
	else
	{
		if (!vPath.security.session.empty())
		{
			return authorizeSession(request, vPath, username);
		}
		else if (request.hasCredentials())
		{
			return authorizeBasic(request, vPath, username);
		}
	}
	return false;
}


bool WebServerDispatcher::authorizeSession(Poco::Net::HTTPServerRequest& request, const VirtualPath& vPath, std::string& username) const
{
	WebSessionManager::Ptr pSessionManager = sessionManager();
	if (pSessionManager)
	{
		WebSession::Ptr pSession = pSessionManager->find(vPath.security.session, request);
		if (pSession)
		{
			username = pSession->getValue<std::string>("username", "");
			if (!username.empty())
			{
				AuthService::Ptr pAuthService = authService();
				if (pAuthService->authorize(username, vPath.security.permission))
				{
					return true;
				}
				else
				{
					_pContext->logger().warning(Poco::format("User %s does not have the permission (%s) to access %s.", username, vPath.security.permission, request.getURI()));
				}
			}
			else
			{
				_pContext->logger().warning(Poco::format("Failed to authorize user for path %s because session is not authenticated.", request.getURI()));
			}
		}
		else
		{
			_pContext->logger().warning(Poco::format("Failed to authorize user for path %s because no session is available.", request.getURI()));
		}
	}
	else 
	{
		_pContext->logger().warning(Poco::format("Failed to authorize user for path %s via session because no WebSessionManager is available.", request.getURI()));
	}
	return false;
}


bool WebServerDispatcher::authorizeBasic(Poco::Net::HTTPServerRequest& request, const VirtualPath& vPath, std::string& username) const
{
	AuthService::Ptr pAuthService = authService();
	if (pAuthService)
	{
		HTTPBasicCredentials cred(request);
		username = cred.getUsername();
		if (pAuthService->authenticate(username, cred.getPassword()))
		{
			if (pAuthService->authorize(username, vPath.security.permission))
			{
				return true;
			}
			else
			{
				_pContext->logger().warning(Poco::format("User %s does not have the permission (%s) to access %s.", username, vPath.security.permission, request.getURI()));
			}
		}
		else
		{
			_pContext->logger().warning(Poco::format("User %s failed authentication.", username));
		}	
	}
	return false;
}


void WebServerDispatcher::sendFound(Poco::Net::HTTPServerRequest& request, const std::string& path)
{
	request.response().set("Location", path);
	sendResponse(request, HTTPResponse::HTTP_FOUND, formatMessage("redirect", path));
}


void WebServerDispatcher::sendNotFound(Poco::Net::HTTPServerRequest& request, const std::string& path)
{
	sendResponse(request, HTTPResponse::HTTP_NOT_FOUND, formatMessage("notfound", path));
}


void WebServerDispatcher::sendNotAuthorized(Poco::Net::HTTPServerRequest& request, const std::string& path)
{
	sendResponse(request, HTTPResponse::HTTP_UNAUTHORIZED, formatMessage("notauth", path));
}


void WebServerDispatcher::sendForbidden(Poco::Net::HTTPServerRequest& request, const std::string& path)
{
	sendResponse(request, HTTPResponse::HTTP_FORBIDDEN, formatMessage("forbidden", path));
}


void WebServerDispatcher::sendBadRequest(Poco::Net::HTTPServerRequest& request, const std::string& message)
{
	sendResponse(request, HTTPResponse::HTTP_BAD_REQUEST, message);
}


void WebServerDispatcher::sendMethodNotAllowed(Poco::Net::HTTPServerRequest& request, const std::string& message)
{
	sendResponse(request, HTTPResponse::HTTP_METHOD_NOT_ALLOWED, message);
}

	
void WebServerDispatcher::sendInternalError(Poco::Net::HTTPServerRequest& request, const std::string& message)
{
	sendResponse(request, HTTPResponse::HTTP_INTERNAL_SERVER_ERROR, message);
}


void WebServerDispatcher::sendResponse(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPResponse::HTTPStatus status, const std::string& message)
{
	if (!request.response().sent())
	{
		const std::string& softwareVersion = request.serverParams().getSoftwareVersion();
		request.response().setContentType("text/html");
		request.response().setStatusAndReason(status);
		std::string html("<HTML><HEAD><TITLE>");
		html += NumberFormatter::format(static_cast<int>(status));
		html += " - ";
		html += request.response().getReasonForStatus(status);
		html += "</TITLE></HEAD><BODY><H1>";
		html += NumberFormatter::format(static_cast<int>(status));
		html += " - ";
		html += request.response().getReasonForStatus(status);
		html += "</H1><P>";
		html += htmlize(message);
		html += "</P><HR><ADDRESS>";
		html += htmlize(softwareVersion);
		html += " at ";
		html += request.serverAddress().toString();
		html += "</ADDRESS></BODY></HTML>";
		request.response().sendBuffer(html.data(), html.size());
	}
	else
	{
		std::string msg("Cannot send response (\"");
		msg += message;
		msg += "\") because a response has already been sent for this request.";
		_pContext->logger().warning(msg);
	}
}


std::string WebServerDispatcher::htmlize(const std::string& str)
{
	std::string::const_iterator it(str.begin());
	std::string::const_iterator end(str.end());
	std::string html;
	for (; it != end; ++it)
	{
		switch (*it)
		{
		case '<': html += "&lt;"; break;
		case '>': html += "&gt;"; break;
		case '"': html += "&quot;"; break;
		case '&': html += "&amp;"; break;
		default:  html += *it; break;
		}
	}
	return html;
}


Poco::OSP::Auth::AuthService::Ptr WebServerDispatcher::authService() const
{	
	Poco::FastMutex::ScopedLock lock(_authServiceMutex);
	
	if (!_pAuthService && !_authServiceName.empty())
	{
		if (!_authServiceName.empty())
		{
			ServiceRef::Ptr pAuthRef = _pContext->registry().findByName(_authServiceName);
			if (pAuthRef)
			{
				_pAuthService = pAuthRef->castedInstance<AuthService>();
			}
			else
			{
				std::string msg("No auth service (");
				msg += _authServiceName;
				msg += ") is available.";
				_pContext->logger().warning(msg);
			}
		}
	}
	return _pAuthService;
}


WebSessionManager::Ptr WebServerDispatcher::sessionManager() const
{
	Poco::FastMutex::ScopedLock lock(_sessionManagerMutex);

	Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = _pContext->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
	if (pWebSessionManagerRef)
	{
		_pSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
	}
	
	return _pSessionManager;
}


std::string WebServerDispatcher::formatMessage(const std::string& messageId, const std::string& arg1, const std::string& arg2)
{
	std::string message;
	std::string realId("message.");
	realId += messageId;
	std::string rawMessage(_pContext->thisBundle()->properties().getString(realId, ""));
	if (rawMessage.empty())
	{
		message = "Message not found: ";
		message += realId;
	}	
	else
	{
		std::string::const_iterator it(rawMessage.begin());
		std::string::const_iterator end(rawMessage.end());
		while (it != end)
		{
			if (*it == '$')
			{
				++it;
				if (it != end)
				{
					if (*it == '1')
						message += arg1;
					else if (*it == '2')
						message += arg2;
					else
						message += *it;
					++it;
				}
				else message += '$';
			}
			else message += *it++;
		}
	}
	return message;
}


bool WebServerDispatcher::shouldCompressMediaType(const std::string& mediaType) const
{
	std::string::size_type endPos = mediaType.find(';');
	std::string mt(mediaType, 0, endPos);
	if (_compressedMediaTypes.find(mt) != _compressedMediaTypes.end())
		return true;
		
	endPos = mt.find('/');
	if (endPos != std::string::npos)
	{
		mt.resize(endPos);
		mt.append("/*");
		return _compressedMediaTypes.find(mt) != _compressedMediaTypes.end();
	}
	else return false;
}


} } } // namespace Poco::OSP::Web
