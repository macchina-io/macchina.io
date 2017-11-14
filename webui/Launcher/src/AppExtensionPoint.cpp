//
// AppExtensionPoint.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "AppExtensionPoint.h"


namespace IoT {
namespace Web {
namespace Launcher {


std::string AppExtensionPoint::ID("io.macchina.web.launcher");


AppExtensionPoint::AppExtensionPoint(Poco::OSP::BundleContext::Ptr pContext, AppRegistry::Ptr pAppRegistry):
	_pContext(pContext),
	_pAppRegistry(pAppRegistry)
{
}

void AppExtensionPoint::handleExtension(Poco::OSP::Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	AppRegistry::App app;
	app.id         = pBundle->properties().expand(pExtensionElem->getAttribute("id"));
	app.title      = pBundle->properties().expand(pExtensionElem->getAttribute("title"));
	app.path       = pBundle->properties().expand(pExtensionElem->getAttribute("path"));
	app.tooltip    = pBundle->properties().expand(pExtensionElem->getAttribute("tooltip"));
	app.icon       = pBundle->properties().expand(pExtensionElem->getAttribute("icon"));
	app.permission = pBundle->properties().expand(pExtensionElem->getAttribute("permission"));
	app.pBundle = pBundle;
	
	if (app.id.empty())
	{
		app.id = app.pBundle->symbolicName();
	}
	
	if (app.icon.empty())
	{
		app.icon = _pContext->thisBundle()->properties().getString("app.defaultIcon");
	}
	
	if (app.tooltip.empty())
	{
		app.tooltip = app.title;
	}

	if (_pContext->logger().information())
	{
		_pContext->logger().information("Registering application: " + app.id);
	}

	_pAppRegistry->add(app);
}


} } } // namespace IoT::Web::Launcher
