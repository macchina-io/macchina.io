//
// JSExtensionPoint.h
//
// $Id: //poco/1.4/OSP/JS/src/JSExtensionPoint.h#1 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_JSExtensionPoint_INCLUDED
#define OSP_JS_JSExtensionPoint_INCLUDED


#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "JSExecutor.h"
#include <vector>


namespace Poco {
namespace OSP {
namespace JS {


class JSExtensionPoint: public Poco::OSP::ExtensionPoint
	/// An extension point for starting JavaScript scripts contained
	/// in bundles.
	///
	/// The following extension point attributes are supported:
	///   - script: path (bundle resource) to the script to be executed
	///   - memoryLimit: size limit for JavaScript allocated memory (default 1 MB)
{
public:
	JSExtensionPoint(BundleContext::Ptr pContext);
		/// Creates the JavaScript extension point.
	
	// Poco::OSP::ExtensionPoint
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

private:
	BundleContext::Ptr _pContext;
	std::vector<TimedJSExecutor::Ptr> _executors;
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_JSExtensionPoint_INCLUDED
