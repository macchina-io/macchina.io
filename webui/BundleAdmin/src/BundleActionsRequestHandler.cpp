//
// BundleActionsRequestHandler.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BundleActionsRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/BundleInstallerService.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/NumberParser.h"
#include "Utility.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


class InstallPartHandler: public Poco::Net::PartHandler
{
public:
	InstallPartHandler(Poco::Net::HTMLForm& form, Poco::OSP::BundleInstallerService::Ptr pInstaller):
		_pInstaller(pInstaller),
		_form(form)
	{
	}
	
	void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
	{
		std::string symbolicName;
		if (_form.has("symbolicName"))
		{
			symbolicName = _form.get("symbolicName");
		}

		if (header.has("Content-Disposition"))
		{
			if (symbolicName.empty())
			{
				_pBundle = _pInstaller->installBundle(stream);
			}
			else
			{
				_pBundle = _pInstaller->replaceBundle(symbolicName, stream);
			}
		}
	}
	
	Poco::OSP::Bundle::Ptr bundle() const
	{
		return _pBundle;
	}
		
private:
	Poco::OSP::BundleInstallerService::Ptr _pInstaller;
	Poco::Net::HTMLForm& _form;
	Poco::OSP::Bundle::Ptr _pBundle;
};


BundleActionsRequestHandler::BundleActionsRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void BundleActionsRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"), request);
		}
	}
	if (!Utility::isAuthenticated(pSession, response)) return;

	std::string username = pSession->getValue<std::string>("username");
	Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth");

	if (!pAuthService->authorize(username, "bundleAdmin"))
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}
	
	std::string symbolicName;
	std::string bundleState;
	std::string error;
	Poco::OSP::BundleInstallerService::Ptr pBundleInstaller = Poco::OSP::ServiceFinder::find<Poco::OSP::BundleInstallerService>(context());
	Poco::Net::HTMLForm form;
	InstallPartHandler installHandler(form, pBundleInstaller);
	try
	{
		form.load(request, request.stream(), installHandler);
	}
	catch (Poco::Exception& exc)
	{
		error = exc.displayText();
		context()->logger().error(Poco::format("Installing or upgrading bundle failed: %s", error));
	}
	Poco::OSP::Bundle::Ptr pBundle = installHandler.bundle();
	if (pBundle)
	{
		symbolicName = pBundle->symbolicName();
		// try to resolve bundle
		try
		{
			pBundle->resolve();
		}
		catch (Poco::Exception& exc)
		{
			error = exc.displayText();
			context()->logger().error(Poco::format("Failed to resolve bundle %s: %s", symbolicName, error));
		}
		bundleState = pBundle->stateString();
	}
	else if (error.empty())
	{
		if (form.has("id"))
		{
			int id;
			if (Poco::NumberParser::tryParse(form.get("id", ""), id))
			{
				pBundle = context()->findBundle(id);
			}
			else
			{
				response.setContentLength(0);
				response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
				response.send();
				return;
			}
		}
		else if (form.has("symbolicName"))
		{
			pBundle = context()->findBundle(form.get("symbolicName"));
		}

		std::string action = form.get("action", "");
		if (pBundle)
		{
			context()->logger().debug(Poco::format("Performing action %s on bundle %s.", action, pBundle->symbolicName()));
			try
			{
				if (action == "start")
				{
					pBundle->start();
				}
				else if (action == "stop")
				{
					pBundle->stop();
				}
				else if (action == "resolve")
				{
					pBundle->resolve();
				}
				else if (action == "uninstall")
				{
					pBundle->uninstall();
				}
			}
			catch (Poco::Exception& exc)
			{
				error = exc.displayText();
				context()->logger().error(Poco::format("Action %s on bundle %s failed: %s", action, pBundle->symbolicName(), error));
			}
			symbolicName = pBundle->symbolicName();
			bundleState = pBundle->stateString();
		}
		else
		{
			error = "Bundle not found";
		}
	}
	
	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	response.send()
		<< "{"
		<< "\"symbolicName\":" << Utility::jsonize(symbolicName) << ","
		<< "\"bundleState\":" << Utility::jsonize(bundleState) << ","
		<< "\"error\":" << Utility::jsonize(error)
		<< "}";
}


Poco::Net::HTTPRequestHandler* BundleActionsRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new BundleActionsRequestHandler(context());
}


} } } // namespace IoT::Web::BundleAdmin
