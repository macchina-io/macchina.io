//
// ExportRequestHandler.cpp
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "ExportRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/Application.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Format.h"
#include "Poco/AutoPtr.h"
#include "Utility.h"


using namespace std::string_literals;


namespace IoT {
namespace Web {
namespace Settings {


ExportRequestHandler::ExportRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void ExportRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
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

	bool authorized = false;
	if (pSession)
	{
		std::string username = pSession->getValue<std::string>("username"s);
		Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth"s);
		authorized = pAuthService->authorize(username, "settingsAdmin"s);
	}

	if (!authorized)
	{
		_pContext->logger().warning("Not authorized to export settings."s);
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	response.setContentType("text/plain"s);
	response.set("Content-Disposition"s, "attachment; filename=\"macchina-settings.properties\""s);

	if (request.getMethod() == "HEAD")
	{
		response.send();
		return;
	}

	response.setChunkedTransferEncoding(true);

	std::ostream& ostream = response.send();
	ostream << "# Settings exported " << Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::SORTABLE_FORMAT) << "\n\n";

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
	}
	if (!pSettings)
	{
		_pContext->logger().warning("No 'macchina.settings' in application configuration."s);
		pSettings = new Poco::Util::PropertyFileConfiguration;
	}
	pSettings->save(ostream);
}


Poco::Net::HTTPRequestHandler* ExportRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new ExportRequestHandler(context());
}


} } } // namespace IoT::Web::Settings
