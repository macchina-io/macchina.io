//
// ImportRequestHandler.cpp
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "ImportRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/Util/Application.h"
#include "Poco/StreamCopier.h"
#include "Poco/Format.h"
#include "Poco/AutoPtr.h"
#include "Utility.h"
#include <sstream>


using namespace std::string_literals;


namespace IoT {
namespace Web {
namespace Settings {


class SettingsPartHandler: public Poco::Net::PartHandler
{
public:
	void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
	{
		try
		{
			_pSettings = new Poco::Util::PropertyFileConfiguration(stream);
		}
		catch (Poco::Exception&)
		{
			_pSettings.reset();
		}
	}

	Poco::Util::PropertyFileConfiguration::Ptr settings() const
	{
		return _pSettings;
	}

private:
	Poco::Util::PropertyFileConfiguration::Ptr _pSettings;
};


ImportRequestHandler::ImportRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void ImportRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::FastMutex::ScopedLock lock(Utility::mutex);

	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"s), request);
		}
	}
	if (!Utility::isAuthenticated(pSession, request, response)) return;

	std::string username = pSession->getValue<std::string>("username"s);
	Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth"s);

	if (!pAuthService->authorize(username, "settingsAdmin"s))
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	try
	{
		SettingsPartHandler settingsHandler;
		Poco::Net::HTMLForm form(request, request.stream(), settingsHandler);

		Poco::Util::PropertyFileConfiguration::Ptr pImportedSettings = settingsHandler.settings();
		if (pImportedSettings)
		{
			Poco::Util::Application& app = Poco::Util::Application::instance();
			std::string settingsPath = app.config().getString("macchina.settings.path"s, ""s);
			Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pSettings;

			if (!settingsPath.empty())
			{
				Poco::AutoPtr<Poco::Util::AbstractConfiguration> pConf = app.config().find("macchina.settings"s);
				if (pConf)
				{
					pSettings = pConf.cast<Poco::Util::PropertyFileConfiguration>();
				}

				if (!pSettings)
				{
					_pContext->logger().warning("No 'macchina.settings' in application configuration."s);
					pSettings = new Poco::Util::PropertyFileConfiguration;
				}

				std::set<std::string> excludeSet;
				Utility::copyProperties(*pImportedSettings, *pSettings, excludeSet, ""s);
				pSettings->save(settingsPath);

				_pContext->logger().information("Settings saved to \"%s\"."s, settingsPath);

				response.setContentLength(0);
				response.send();
			}
			else
			{
				throw Poco::ApplicationException("No \"macchina.settings.path\" property defined. Cannot save settings."s);
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().log(exc);

		response.setContentType("application/json"s);
		response.setChunkedTransferEncoding(true);
		response.send()
			<< "{"
			<<   "\"error\":" << Utility::jsonize(exc.displayText())
			<< "}";
		return;
	}
}


Poco::Net::HTTPRequestHandler* ImportRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new ImportRequestHandler(context());
}


} } } // namespace IoT::Web::Settings
