//
// WebFilterExtensionPoint.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebFilterExtensionPoint.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebFilterExtensionPoint
//
// Definition of the WebFilterExtensionPoint class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Web_WebFilterExtensionPoint_INCLUDED
#define OSP_Web_WebFilterExtensionPoint_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/Web/WebFilterFactory.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/ClassLoader.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include <map>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebFilterExtensionPoint: public ExtensionPoint
	/// WebServerExtension handles the "osp.web.server.filter" extensions point.
	///
	/// To register a Filter, for processing a resource before
	/// it's being sent as response:
	///
	///     <extension point="osp.web.server.filter"
	///                mediaType="media/type"
	///                class="MyFilterFactory"
	///                library="MyLib"/>
	///
	/// Note that the extension points are automatically removed if a bundle is stopped.
	///
	/// The following attributes can be specified for "osp.web.server.directory":
	///    * mediaType:   The media type this filter applies to. Every resource having
	///                   this media type will be passed to the filter.
	///    * class: the class name of the request handler factory.
	///    * library: the name of the shared library containing the request handler factory. 
	///
	/// Any additional attributes are passed to the factory's createFilter() method.
{
public:
	WebFilterExtensionPoint(BundleContext::Ptr pContext, WebServerDispatcher* pDispatcher);
		/// Creates the WebServerExtension. Expects a not null pointer to the Web which must be valid during the whole
		/// life-time of the extension object

	~WebFilterExtensionPoint();
		/// Destroys the WebServerExtension.

	// ExtensionPoint
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

	static const std::string EXTPOINT_FILTER;

protected:
	void handleFilter(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

	void onBundleStopped(const void* pSender, BundleEvent& ev);
		/// When a bundle is stopped, all of its request handlers and mappings are automatically disabled.

	static const std::string ATTR_CLASS;
	static const std::string ATTR_LIBRARY;
	static const std::string ATTR_MEDIATYPE;
	static const std::string MANIFEST_NAME;

private:
	WebFilterExtensionPoint();
	
	typedef Poco::SharedPtr<WebFilterFactory> FactoryPtr;
	typedef Poco::ClassLoader<WebFilterFactory> Loader;
	typedef std::map<std::string, Bundle::Ptr> LibBundleMap;
	typedef std::multimap<Bundle::Ptr, std::string> BundleFilterMap;
	
	BundleContext::Ptr   _pContext;
	WebServerDispatcher* _pDispatcher;
	Loader               _loader;
	LibBundleMap         _libBundleMap;
	BundleFilterMap      _bundleFilterMap;
	Poco::FastMutex      _mutex;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebFilterExtensionPoint_INCLUDED
