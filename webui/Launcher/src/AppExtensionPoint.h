//
// AppExtensionPoint.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef Launcher_AppExtensionPoint_INCLUDED
#define Launcher_AppExtensionPoint_INCLUDED


#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "AppRegistry.h"


namespace IoT {
namespace Web {
namespace Launcher {


class AppExtensionPoint: public Poco::OSP::ExtensionPoint
{
public:
	AppExtensionPoint(Poco::OSP::BundleContext::Ptr pContext, AppRegistry::Ptr pAppRegistry);
		/// Creates the LauncherExtensionPOint
	
	// ExtensionPoint
	void handleExtension(Poco::OSP::Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

	static std::string ID;

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	AppRegistry::Ptr _pAppRegistry;
};


} } } // namespace IoT::Web::Launcher


#endif // Launcher_AppExtensionPoint_INCLUDED
