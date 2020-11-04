//
// JSExtensionPoint.h
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_JSExtensionPoint_INCLUDED
#define OSP_JS_JSExtensionPoint_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/Mutex.h"
#include <vector>


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API JSExtensionPoint: public Poco::OSP::ExtensionPoint
	/// An extension point for starting JavaScript scripts contained
	/// in bundles.
	///
	/// The following extension point attributes are supported:
	///   - script: path (bundle resource) to the script to be executed
	///   - memoryLimit: size limit for JavaScript allocated memory (default 1 MB)
{
public:
	using Ptr = Poco::AutoPtr<JSExtensionPoint>;

	JSExtensionPoint(BundleContext::Ptr pContext);
		/// Creates the JavaScript extension point.

	~JSExtensionPoint();
		/// Destroys the JavaScript extension point.

	// Poco::OSP::ExtensionPoint
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

protected:
	void onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev);

private:
	BundleContext::Ptr _pContext;
	std::vector<TimedJSExecutor::Ptr> _executors;
	Poco::FastMutex _mutex;
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_JSExtensionPoint_INCLUDED
