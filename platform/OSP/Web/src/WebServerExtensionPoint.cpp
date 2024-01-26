//
// WebServerExtensionPoint.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerExtensionPoint
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/WebServerExtensionPoint.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/OSPException.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/StringTokenizer.h"
#include "Poco/String.h"
#include "Poco/Delegate.h"


using Poco::FastMutex;
using Poco::Delegate;


namespace Poco {
namespace OSP {
namespace Web {


const std::string WebServerExtensionPoint::EXTPOINT_DIRECTORY("osp.web.server.directory");
const std::string WebServerExtensionPoint::EXTPOINT_HANDLER("osp.web.server.requesthandler");
const std::string WebServerExtensionPoint::ATTR_PATH("path");
const std::string WebServerExtensionPoint::ATTR_PATTERN("pattern");
const std::string WebServerExtensionPoint::ATTR_METHODS("methods");
const std::string WebServerExtensionPoint::ATTR_DESCRIPTION("description");
const std::string WebServerExtensionPoint::ATTR_SECURE("secure");
const std::string WebServerExtensionPoint::ATTR_REALM("realm");
const std::string WebServerExtensionPoint::ATTR_PERMISSION("permission");
const std::string WebServerExtensionPoint::ATTR_AUTHMETHODS("authMethods");
const std::string WebServerExtensionPoint::ATTR_SESSION("session");
const std::string WebServerExtensionPoint::ATTR_CSRFPROTECTION("csrfProtection");
const std::string WebServerExtensionPoint::ATTR_CSRFTOKENHEADER("csrfTokenHeader");
const std::string WebServerExtensionPoint::ATTR_RESOURCE("resource");
const std::string WebServerExtensionPoint::ATTR_CLASS("class");
const std::string WebServerExtensionPoint::ATTR_LIBRARY("library");
const std::string WebServerExtensionPoint::ATTR_ALLOWSPECIALIZATION("allowSpecialization");
const std::string WebServerExtensionPoint::ATTR_INDEX("index");
const std::string WebServerExtensionPoint::ATTR_HIDDEN("hidden");
const std::string WebServerExtensionPoint::ATTR_CACHE("cache");
const std::string WebServerExtensionPoint::ATTR_EXACTMATCH("exactMatch");
const std::string WebServerExtensionPoint::ATTR_CORS("cors");
const std::string WebServerExtensionPoint::ATTR_ALLOWORIGIN("allowOrigin");
const std::string WebServerExtensionPoint::ATTR_ALLOWMETHODS("allowMethods");
const std::string WebServerExtensionPoint::ATTR_ALLOWHEADERS("allowHeaders");
const std::string WebServerExtensionPoint::ATTR_ALLOWCREDENTIALS("allowCredentials");
const std::string WebServerExtensionPoint::ATTR_RESPONSEFORMAT("responseFormat");
const std::string WebServerExtensionPoint::ATTR_REDIRECTON401("redirectOn401");
const std::string WebServerExtensionPoint::MANIFEST_NAME("WebServer");


WebServerExtensionPoint::WebServerExtensionPoint(BundleContext::Ptr pContext, WebServerDispatcher* pDispatcher):
	_pContext(pContext),
	_pDispatcher(pDispatcher)
{
	poco_check_ptr (_pDispatcher);

	_pContext->events().bundleStopped += Delegate<WebServerExtensionPoint, BundleEvent>(this, &WebServerExtensionPoint::onBundleStopped);
}


WebServerExtensionPoint::~WebServerExtensionPoint()
{
	try
	{
		_pContext->events().bundleStopped -= Delegate<WebServerExtensionPoint, BundleEvent>(this, &WebServerExtensionPoint::onBundleStopped);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void WebServerExtensionPoint::handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	FastMutex::ScopedLock lock(_mutex);

	if (pExtensionElem)
	{
		const Poco::XML::XMLString& extPoint = pExtensionElem->getAttribute(ExtensionPointService::POINT_ATTR);
		if (extPoint == EXTPOINT_DIRECTORY)
			handleDirectory(pBundle, pExtensionElem);
		else if (extPoint == EXTPOINT_HANDLER)
			handleRequestHandler(pBundle, pExtensionElem);
		else
			throw BundleException("Failed to parse extension point");
	}
}


void WebServerExtensionPoint::handleDirectory(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	WebServerDispatcher::VirtualPath vPath;
	handleCommon(pBundle, pExtensionElem, vPath);
	vPath.resource  = pExtensionElem->getAttribute(ATTR_RESOURCE);
	vPath.indexPage = pExtensionElem->getAttribute(ATTR_INDEX);

	_pDispatcher->addVirtualPath(vPath);
}


void WebServerExtensionPoint::handleRequestHandler(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	WebServerDispatcher::VirtualPath vPath;
	handleCommon(pBundle, pExtensionElem, vPath);

	std::string pattern = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_PATTERN));
	if (!pattern.empty())
	{
		vPath.pPattern = new Poco::RegularExpression(pattern, Poco::RegularExpression::RE_ANCHORED);
		vPath.path     = pattern;
	}

	std::string methods = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_METHODS));
	if (!methods.empty())
	{
		Poco::StringTokenizer tok(methods, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		vPath.methods.insert(tok.begin(), tok.end());
	}

	const std::string& className = pExtensionElem->getAttribute(ATTR_CLASS);

	std::string library = pExtensionElem->getAttribute(ATTR_LIBRARY);
	if (library.empty())
		library = pBundle->symbolicName();

	std::string libraryPath = _pContext->pathForLibrary(library);
	if (!_loader.isLibraryLoaded(libraryPath))
	{
		_loader.loadLibrary(libraryPath, MANIFEST_NAME);
		_libBundleMap[libraryPath] = pBundle;
	}

	FactoryPtr pFactory = _loader.create(className);
	pFactory->init(_pContext->contextForBundle(pBundle));
	vPath.pFactory = pFactory;

	_pDispatcher->addVirtualPath(vPath);
}


void WebServerExtensionPoint::handleCommon(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem, WebServerDispatcher::VirtualPath& vPath)
{
	vPath.pOwnerBundle             = pBundle;
	vPath.path                     = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_PATH));
	vPath.description              = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_DESCRIPTION));
	vPath.security.realm           = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_REALM));
	vPath.security.permission      = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_PERMISSION));
	vPath.security.authMethods     = WebServerDispatcher::parseAuthMethods(pExtensionElem->getAttribute(ATTR_AUTHMETHODS));
	vPath.security.session         = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_SESSION));
	vPath.security.secure          = pExtensionElem->getAttribute(ATTR_SECURE) == "true";
	vPath.security.csrfProtection  = pExtensionElem->getAttribute(ATTR_CSRFPROTECTION) == "true";
	vPath.security.csrfTokenHeader = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_CSRFTOKENHEADER));
	vPath.cors.enable              = pExtensionElem->getAttribute(ATTR_CORS) == "true";
	vPath.cors.allowOrigin         = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_ALLOWORIGIN));
	vPath.cors.allowMethods        = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_ALLOWMETHODS));
	vPath.cors.allowCredentials    = pExtensionElem->getAttribute(ATTR_ALLOWCREDENTIALS) != "false";
	vPath.cors.allowHeaders        = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_ALLOWHEADERS));
	vPath.hidden                   = pExtensionElem->getAttribute(ATTR_HIDDEN) == "true";
	vPath.cache                    = pExtensionElem->getAttribute(ATTR_CACHE) != "false";
	vPath.exactMatch               = pExtensionElem->getAttribute(ATTR_EXACTMATCH) == "true";
	vPath.redirectOn401            = pBundle->properties().expand(pExtensionElem->getAttribute(ATTR_REDIRECTON401));

	if (vPath.security.csrfProtection && vPath.security.csrfTokenHeader.empty())
	{
		vPath.security.csrfTokenHeader = "X-XSRF-TOKEN";
	}

	const std::string& specialization = Poco::toLower(pExtensionElem->getAttribute(ATTR_ALLOWSPECIALIZATION));
	if (specialization.empty() || specialization == "none")
		vPath.security.mode = WebServerDispatcher::SM_NONE;
	else if (specialization == "owner")
		vPath.security.mode = WebServerDispatcher::SM_OWNER;
	else if (specialization == "all")
		vPath.security.mode = WebServerDispatcher::SM_ALL;
	else
		throw BundleException("Failed to parse extension point: Illegal attribute value " + specialization + " for attribute " + ATTR_ALLOWSPECIALIZATION);

	const std::string& responseFormat = Poco::toLower(pExtensionElem->getAttribute(ATTR_RESPONSEFORMAT));
	if (responseFormat.empty() || responseFormat == "html")
		vPath.responseFormat = WebServerDispatcher::RESPONSE_FORMAT_HTML;
	else if (responseFormat == "json")
		vPath.responseFormat = WebServerDispatcher::RESPONSE_FORMAT_JSON;
	else
		throw BundleException("Failed to parse extension point: Illegal attribute value " + responseFormat + " for attribute " + ATTR_RESPONSEFORMAT);
}


void WebServerExtensionPoint::onBundleStopped(const void* pSender, BundleEvent& ev)
{
	FastMutex::ScopedLock lock(_mutex);

	Bundle::ConstPtr pBundle = ev.bundle();
	LibBundleMap::iterator it = _libBundleMap.begin();
	while (it != _libBundleMap.end())
	{
		if (it->second == pBundle)
		{
			_pDispatcher->removeBundle(it->second);
			_loader.unloadLibrary(it->first);
			LibBundleMap::iterator delIt(it);
			++it;
			_libBundleMap.erase(delIt);
		}
		else ++it;
	}
}


} } } // namespace Poco::OSP::Web
