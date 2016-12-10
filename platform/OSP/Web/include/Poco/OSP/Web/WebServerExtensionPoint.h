//
// WebServerExtensionPoint.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebServerExtensionPoint.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerExtensionPoint
//
// Definition of the WebServerExtensionPoint class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Web_WebServerExtensionPoint_INCLUDED
#define OSP_Web_WebServerExtensionPoint_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/ClassLoader.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include <map>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebServerExtensionPoint: public ExtensionPoint
	/// WebServerExtension handles two extensions points.
	/// To register a directory in the Webserver:
	///     <extension point="osp.web.server.directory" 
	///                path="URI" 
	///                resource="dir inside bundle" 
	///                allowSpecialization="none|owner|all"
	///                index="index.html"/>
	///
	/// To register a RequestHandlerFactory for a given server uri/set of uris:
	///     <extension point="osp.web.server.requesthandler" 
	///                path="URI"
	///                class="MyRequestHandlerFactory" 
	///                library="MyLib"/>
	///
	/// Note that the extension points are automatically removed if a bundle is stopped.
	///
	/// The following attributes can be specified for both extension points:
	///    * path:        The URI on the server to which the resource or handler is mapped.
	///    * description: User-readable description of resource or handler.
	///    * secure:      If "true", require a secure (HTTPS) connection to access the resource.
	///    * realm:       Specify authentication realm (together with permission).
	///    * permission:  Specify the necessary access permission for this resource.
	///                   Unless a session name is specified, HTTP Basic Authentication 
	///                   is used to obtain the user's user name and password, which are 
	///                   then checked against the specified permission using the authorization 
	///                   service.
	///    * session:     Specify the name of the session used for session-based 
	///                   authentication instead of HTTP Basic Authentication.
	///                   If specified together with a permission, the session with the
	///                   specified name is obtained from the WebSessionService, and the
	///                   current users's name is obtained from the session's "username"
	///                   attribute, which must be a std::string. 
	///    * hidden:      If "true", path is not included by WebServerDispatcher::listVirtualPaths().
	///
	/// The following attributes can be specified for "osp.web.server.directory":
	///    * resource:    Specify a directory within the bundle where the HTML, image
	///                   and other files are located.
	///    * index:       Specify the name of the default document (defaults to "index.html").
	///    * cache:       If "true", files in this directory can be cached.
	///                   Defaults to "true". Set to "false" to disable caching.
	///    * allowSpecialization: 
	///                   Using the <[allowSpecialization]> attribute, a bundle can specify whether 
	///                   other bundles can register themselves for subdirectories of the directory 
	///                   specified in <[path]>. The following values are supported:
	///                   none: it is impossible to map resources or request handlers to subdirectories;
	///                   owner: only this bundle can map resources or request handlers to subdirectories;
	///                   all: any bundle can map resources or request handlers to subdirectories.
	///
	/// The following attributes can be specified for "osp.web.server.requesthandler":
	///    * pattern:     A regular expression for matching requests to the handler.
	///                   If specified, no path attribute should be specified.
	///                   If both the pattern and path attributes are given, path is ignored.
	///                   Paths containing a pattern are not included by WebServerDispatcher::listVirtualPaths().
	///    * methods:     A comma-separated list of HTTP request methods ("GET", "POST", etc.") supported by the handler.
	///                   If not specified, all methods are passed to the handler.
	///    * class:       The class name of the request handler factory.
	///    * library:     The name of the shared library containing the request handler factory. 
{
public:
	WebServerExtensionPoint(BundleContext::Ptr pContext, WebServerDispatcher* pDispatcher);
		/// Creates the WebServerExtension. Expects a not null pointer to the Web which must be valid during the whole
		/// life-time of the extension object

	~WebServerExtensionPoint();
		/// Destroys the WebServerExtension.

	// ExtensionPoint
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

	static const std::string EXTPOINT_DIRECTORY;
	static const std::string EXTPOINT_HANDLER;

protected:
	void handleDirectory(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);
	void handleRequestHandler(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);
	void handleCommon(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem, WebServerDispatcher::VirtualPath& vPath);

	void onBundleStopped(const void* pSender, BundleEvent& ev);
		/// When a bundle is stopped, all of its request handlers and mappings are automatically disabled.

	static const std::string ATTR_PATH;
	static const std::string ATTR_PATTERN;
	static const std::string ATTR_METHODS;
	static const std::string ATTR_DESCRIPTION;
	static const std::string ATTR_SECURE;
	static const std::string ATTR_REALM;
	static const std::string ATTR_PERMISSION;
	static const std::string ATTR_SESSION;
	static const std::string ATTR_RESOURCE;
	static const std::string ATTR_CLASS;
	static const std::string ATTR_LIBRARY;
	static const std::string ATTR_ALLOWSPECIALIZATION;
	static const std::string ATTR_INDEX;
	static const std::string ATTR_HIDDEN;
	static const std::string ATTR_CACHE;
	static const std::string MANIFEST_NAME;

private:
	WebServerExtensionPoint();
	
	typedef Poco::SharedPtr<WebRequestHandlerFactory> FactoryPtr;
	typedef Poco::ClassLoader<WebRequestHandlerFactory> Loader;
	typedef std::map<std::string, Bundle::Ptr> LibBundleMap;
	
	BundleContext::Ptr   _pContext;
	WebServerDispatcher* _pDispatcher;
	Loader               _loader;
	LibBundleMap         _libBundleMap;
	Poco::FastMutex      _mutex;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebServerExtensionPoint_INCLUDED
