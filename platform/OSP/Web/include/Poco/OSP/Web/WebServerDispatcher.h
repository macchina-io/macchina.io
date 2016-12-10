//
// WebServerDispatcher.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebServerDispatcher.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerDispatcher
//
// Definition of the WebServerDispatcher class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Web_WebServerDispatcher_INCLUDED
#define OSP_Web_WebServerDispatcher_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/MediaTypeMapper.h"
#include "Poco/OSP/Web/WebFilter.h"
#include "Poco/OSP/Web/WebFilterFactory.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/RegularExpression.h"
#include "Poco/Logger.h"
#include "Poco/SharedPtr.h"
#include "Poco/ThreadPool.h"
#include "Poco/Mutex.h"
#include <vector>
#include <map>
#include <set>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebServerDispatcher: public Service
	/// A WebServerDispatcher is some sort of meta HTTPRequestHandlerFactory. It groups together
	/// several other HTTPRequestHandlerFactory instances and distributes requests to them according to the registered
	/// request handler extension points (see the WebServerExtensionPoint class).
{
public:
	enum SpecializationMode
		/// A bundle that registers a resource mapping or request handler for a certain
		/// path can specify whether other bundles can register subdirectories of this directory.
	{
		SM_NONE  = 0, /// No one can register subdirectories
		SM_OWNER = 1, /// Only the owner bundle can register subdirectories
		SM_ALL   = 2  /// Everyone can register subdirectories
	};

	typedef Poco::SharedPtr<Poco::Net::HTTPRequestHandlerFactory> RequestHandlerFactoryPtr;
	typedef Poco::SharedPtr<Poco::RegularExpression> RegularExpressionPtr;
	
	struct PathSecurity
		/// Security attributes for a registered path.
	{
		PathSecurity():
			mode(SM_OWNER),
			secure(false)
		{
		}
		
		PathSecurity(SpecializationMode aMode, const std::string& aRealm, const std::string& aPermission, bool aSecure = false):
			mode(aMode),
			realm(aRealm),
			permission(aPermission),
			secure(aSecure)
		{
		}
		
		SpecializationMode mode;       /// specialization mode (does not apply to pattern)
		std::string        realm;      /// realm if a permission (and thus authentication) is required
		std::string        permission; /// required permission (empty for none)
		std::string        session;    /// name of session for session-based authentication
		bool               secure;     /// path requires secure connection
	};

	struct VirtualPath
		/// A VirtualPath struct is used to specify a path mapping for a bundle.
	{
		VirtualPath():
			hidden(false)
		{
		}
		
		VirtualPath(const std::string& aPath, const std::string& aResource, const PathSecurity& aSecurity, Bundle::ConstPtr pOwner):
			path(aPath),
			resource(aResource),
			security(aSecurity),
			hidden(false),
			cache(true),
			pOwnerBundle(pOwner)
		{
		}
		
		VirtualPath(const std::string& aPath, RequestHandlerFactoryPtr aFactory, const PathSecurity& aSecurity, Bundle::ConstPtr pOwner):
			path(aPath),
			pFactory(aFactory),
			security(aSecurity),
			hidden(false),
			cache(true),
			pOwnerBundle(pOwner)
		{
		}
		
		RegularExpressionPtr     pPattern;     /// pattern for matching request handlers
		std::string              path;         /// virtual server path (e.g., /images)
		std::set<std::string>    methods;      /// allowed methods ("GET", "POST", etc.)
		std::string              description;  /// user-readable description of resource or service
		std::string              resource;     /// resource path (if mapped to resource)
		std::string              indexPage;    /// index page (only used if resource path is set; defaults to "index.html")
		RequestHandlerFactoryPtr pFactory;     /// request handler factory (null if resource path is specified)
		PathSecurity             security;     /// security attributes
		bool                     hidden;       /// path is not included in list returned by listVirtualPaths()
		bool                     cache;        /// resource can be cached
		Bundle::Ptr              pOwnerBundle; /// bundle owning path
	};
	
	struct PathInfo
	{
		std::string description;
		std::string permission;
		std::string session;
		Bundle::Ptr pBundle;
	};
	
	typedef std::map<std::string, VirtualPath> PathMap;
	typedef std::map<std::string, PathInfo> PathInfoMap;
	typedef std::vector<VirtualPath> PatternVec;

	typedef Poco::SharedPtr<WebFilter> WebFilterPtr;
	typedef Poco::SharedPtr<WebFilterFactory> WebFilterFactoryPtr;

	WebServerDispatcher(BundleContext::Ptr pContext, MediaTypeMapper::Ptr pMediaTypeMapper, const std::string& authServiceName, bool compressResponses, const std::set<std::string>& compressedMediaTypes, bool cacheResources = false);
		/// Creates the WebServerDispatcher.

	virtual ~WebServerDispatcher();
		/// Destroys the WebServerDispatcher.

	void addVirtualPath(const VirtualPath& virtualPath);
		/// Adds the given VirtualPath to the path mapping table.
		///
		/// Throws an ExistsException if a mapping for the given path already exists.

	void removeVirtualPath(const std::string& virtualPath);
		/// Removes a path mapping from the path mapping table.
		///
		/// Throws a NotFoundException if the given path does not exist.

	void listVirtualPaths(PathInfoMap& paths) const;
		/// Returns a map containing all virtual paths (key) that are not patterns
		/// and not marked as hidden, and their descriptions (value).
		
	void virtualPathMappings(PathMap& mappings) const;
		/// Returns all path mappings. This member function creates a full
		/// copy of the internal path map.

	void removeBundle(Bundle::ConstPtr pBundle);
		/// Removes all mappings from the given bundle.
		
	void uncacheBundleResources(Bundle::ConstPtr pBundle);
		/// Removes all cached resources from the given bundle form the cache.

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, bool secure);
		/// Handles the given request. Secure specifies whether the request has been
		/// sent over a secure (HTTPS) connection.
		
	Poco::ThreadPool& threadPool();
		/// Returns the thread pool for use by Poco::Net::HTTPServer.

	void addFilter(const std::string& mediaType, WebFilterFactoryPtr pFilterFactory, const WebFilter::Args& args);
		/// Adds a filter factory for the given media type.
		///
		/// Throws a Poco::ExistsException if a filter already exists for the given mediaType.
		
	void removeFilter(const std::string& mediaType);
		/// Removes the filter for the given mediaType.	

	// Service
	virtual const std::type_info& type() const;
	virtual bool isA(const std::type_info& otherType) const;

	static const std::string SERVICE_NAME;
	
protected:
	void onBundleStopping(const void* pSender, BundleEvent& ev);
		/// When a bundle is stopped, all of its request handlers and mappings are automatically disabled.

	static std::string normalizePath(const std::string& path);
		/// Creates normalized path for internal storage.
		/// The normalized path always starts and ends with a slash.
		
	const VirtualPath& mapPath(const std::string& path, const std::string& method) const;
		/// Maps a URI to a VirtualPath.
		///
		/// Throws a NotFoundException if no suitable mapping can be found.

	void sendResource(Poco::Net::HTTPServerRequest& request, const std::string& path, const std::string& vpath, const std::string& resPath, const std::string& resBase, const std::string& index, Bundle::ConstPtr pBundle, bool canCache);
		/// Sends a bundle resource as response.
		
	std::istream* findResource(Bundle::ConstPtr pBundle, const std::string& base, const std::string& res, const std::string& index, std::string& mediaType, std::string& resolvedPath, bool canCache) const;
		/// Returns a resource stream for the given path, or a null pointer
		/// if no matching resource exists.

	std::istream* getCachedResource(Bundle::ConstPtr pBundle, const std::string& path, bool canCache) const;
		/// Returns a resource stream for the given path, or a null pointer
		/// if no matching resource exists. If caching is enabled both globally
		/// and for the specific resource, attempts to cache the resource.

	static bool cleanPath(std::string& path);
		/// Removes unnecessary characters (such as trailing dots)
		/// from the path and checks for illegal or dangerous
		/// characters.
		///
		/// Returns true if the path is okay, false otherwise.

	bool authorize(Poco::Net::HTTPServerRequest& request, const VirtualPath& vPath, std::string& username) const;
		/// Authorizes the request.

	bool authorizeSession(Poco::Net::HTTPServerRequest& request, const VirtualPath& vPath, std::string& username) const;
		/// Authorizes the request using a session-based authentication.

	bool authorizeBasic(Poco::Net::HTTPServerRequest& request, const VirtualPath& vPath, std::string& username) const;
		/// Authorizes the request using a HTTP Basic Authentication.

	void sendFound(Poco::Net::HTTPServerRequest& request, const std::string& path);
		/// Sends a 302 Found response.

	void sendNotFound(Poco::Net::HTTPServerRequest& request, const std::string& path);
		/// Sends a 404 Not Found error response.

	void sendNotAuthorized(Poco::Net::HTTPServerRequest& request, const std::string& path);
		/// Sends a 401 Unauthorized error response.

	void sendForbidden(Poco::Net::HTTPServerRequest& request, const std::string& path);
		/// Sends a 403 Forbidden error response.

	void sendBadRequest(Poco::Net::HTTPServerRequest& request, const std::string& message);
		/// Sends a 404 Not Found error response.

	void sendMethodNotAllowed(Poco::Net::HTTPServerRequest& request, const std::string& message);
		/// Sends a 405 Method Not Allowed error response.
		
	void sendInternalError(Poco::Net::HTTPServerRequest& request, const std::string& message);
		/// Sends a 500 Internal Server Error response.

	void sendResponse(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPResponse::HTTPStatus status, const std::string& message);
		/// Sends a standard status/error response.

	static std::string htmlize(const std::string& str);
		/// Returns a HTML-ized version of the given string.

	Poco::OSP::Auth::AuthService::Ptr authService() const;
		/// Returns a pointer to the auth service, if it is available,
		/// or null otherwise.
		
	WebSessionManager::Ptr sessionManager() const;
		/// Returns a pointer to the WebSessionManager.
		
	std::string formatMessage(const std::string& messageId, const std::string& arg1 = std::string(), const std::string& arg2 = std::string());
		/// Reads a message from the bundle.properties resource and replaces
		/// placeholders $1 and $2 with arg1 and arg2, respectively.
		
	bool shouldCompressMediaType(const std::string& mediaType) const;
		/// Returns true iff content with the given media type should be compressed.
		
	WebFilterPtr findFilter(const std::string& mediaType);
		/// Returns a WebFilter instance for the given mediaType, or a null
		/// pointer if no WebFilterFactory has been registered for the given
		/// mediaType.
		
	void logRequest(const Poco::Net::HTTPServerRequest& request, const Poco::Net::HTTPServerResponse& response, const std::string& username);
		/// Logs the HTTP request.
		
private:
	struct WebFilterFactoryInfo
	{
		WebFilterFactoryPtr pFactory;
		WebFilter::Args args;
	};
	typedef std::map<std::string, WebFilterFactoryInfo> FilterFactoryMap;
	typedef std::map<std::string, std::string> ResourceCache;
	
	BundleContext::Ptr _pContext;
	MediaTypeMapper::Ptr _pMediaTypeMapper;
	PathMap _pathMap;
	PatternVec _patternVec;
	std::string _authServiceName;
	bool _compressResponses;
	std::set<std::string> _compressedMediaTypes;
	bool _cacheResources;
	mutable Poco::OSP::Auth::AuthService::Ptr _pAuthService;
	mutable WebSessionManager::Ptr _pSessionManager;
	mutable ResourceCache _resourceCache;
	mutable Poco::FastMutex _resourceCacheMutex;
	FilterFactoryMap _filterFactoryMap;
	mutable Poco::FastMutex _filterFactoryMutex;
	Poco::ThreadPool _threadPool;
	mutable Poco::FastMutex _mutex;
	mutable Poco::FastMutex _authServiceMutex;
	mutable Poco::FastMutex _sessionManagerMutex;
	Poco::Logger& _accessLogger;
};


//
// inlines
//
inline Poco::ThreadPool& WebServerDispatcher::threadPool()
{
	return _threadPool;
}


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebServerDispatcher_INCLUDED
