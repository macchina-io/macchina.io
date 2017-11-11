//
// BundleListRequestHandler.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BundleListRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Utility.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


BundleListRequestHandler::BundleListRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void BundleListRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
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

	response.setChunkedTransferEncoding(true);
	response.setContentType("application/json");
	std::ostream& ostr = response.send();
	
	ostr << "[";
	std::vector<Poco::OSP::Bundle::Ptr> bundles;
	_pContext->listBundles(bundles);
	for (std::vector<Poco::OSP::Bundle::Ptr>::const_iterator it = bundles.begin(); it != bundles.end(); ++it)
	{
		if (it != bundles.begin()) ostr << ",";
		ostr 
			<< "{"
			<< "\"id\":" << (*it)->id() << ","
			<< "\"symbolicName\":" << Utility::jsonize((*it)->symbolicName()) << ","
			<< "\"name\":" << Utility::jsonize((*it)->name()) << ","
			<< "\"version\":" << Utility::jsonize((*it)->version().toString()) << ","
			<< "\"vendor\":" << Utility::jsonize((*it)->vendor()) << ","
			<< "\"state\":" << Utility::jsonize((*it)->stateString())
			<< "}";
	}
	ostr << "]";
}


Poco::Net::HTTPRequestHandler* BundleListRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new BundleListRequestHandler(context());
}


} } } // namespace IoT::Web::BundleAdmin
