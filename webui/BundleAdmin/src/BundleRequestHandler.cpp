//
// BundleRequestHandler.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/NumberParser.h"
#include "Utility.h"


using namespace std::string_literals;


namespace IoT {
namespace Web {
namespace BundleAdmin {


BundleRequestHandler::BundleRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void BundleRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
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

	if (!pAuthService->authorize(username, "bundleAdmin"s))
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	Poco::OSP::Bundle::Ptr pBundle;
	Poco::Net::HTMLForm form(request, request.stream());
	if (form.has("id"))
	{
		int id;
		if (Poco::NumberParser::tryParse(form.get("id"s, ""s), id))
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
		pBundle = context()->findBundle(form.get("symbolicName"s));
	}

	if (!pBundle)
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		response.send();
		return;
	}

	response.setChunkedTransferEncoding(true);
	response.setContentType("application/json"s);
	std::ostream& ostr = response.send();

	ostr
		<< "{"
		<< "\"id\":" << pBundle->id() << ","
		<< "\"symbolicName\":" << Utility::jsonize(pBundle->symbolicName()) << ","
		<< "\"name\":" << Utility::jsonize(pBundle->name()) << ","
		<< "\"version\":" << Utility::jsonize(pBundle->version().toString()) << ","
		<< "\"state\":" << Utility::jsonize(pBundle->stateString()) << ","
		<< "\"vendor\":" << Utility::jsonize(pBundle->vendor()) << ","
		<< "\"copyright\":" << Utility::jsonize(pBundle->copyright()) << ","
		<< "\"runlevel\":" << Utility::jsonize(pBundle->runLevel()) << ","
		<< "\"lazyStart\":" << (pBundle->lazyStart() ? "true" : "false") << ","
		<< "\"sealed\":" << (pBundle->sealed() ? "true" : "false") << ","
		<< "\"preventUninstall\":" << (pBundle->preventUninstall() ? "true" : "false") << ","
		<< "\"path\":" << Utility::jsonize(pBundle->path()) << ","
		<< "\"requires\": [";

	const Poco::OSP::BundleManifest::Dependencies& deps = pBundle->requiredBundles();
	for (Poco::OSP::BundleManifest::Dependencies::const_iterator itDep = deps.begin(); itDep != deps.end(); ++itDep)
	{
		if (itDep != deps.begin()) ostr << ",";
		ostr
			<< "{"
			<< "\"symbolicName\":" << Utility::jsonize(itDep->symbolicName) << ","
			<< "\"versions\":" << Utility::jsonize(itDep->versions.toString())
			<< "}";
	}
	ostr
		<< "],"
		<< "\"requiredBy\": [";

	BundleVec depending;
	dependingBundles(pBundle, depending, false);
	for (BundleVec::const_iterator itDep = depending.begin(); itDep != depending.end(); ++itDep)
	{
		if (itDep != depending.begin()) ostr << ",";
		ostr
			<< "{"
			<< "\"symbolicName\":" << Utility::jsonize((*itDep)->symbolicName()) << ","
			<< "\"versions\":" << Utility::jsonize((*itDep)->version().toString())
			<< "}";
	}

	ostr
		<< "],"
		<< "\"modules\": {";

	ostr << "\"provides\": [";

	const Poco::OSP::Bundle::Modules& mods = pBundle->providedModules();
	for (Poco::OSP::Bundle::Modules::const_iterator itMod = mods.begin(); itMod != mods.end(); ++itMod)
	{
		if (itMod != mods.begin()) ostr << ",";
		ostr
			<< "{"
			<< "\"symbolicName\":" << Utility::jsonize(itMod->symbolicName) << ","
			<< "\"version\":" << Utility::jsonize(itMod->version.toString())
			<< "}";
	}

	ostr
		<< "],"
		<< "\"requires\": [";

	const Poco::OSP::BundleManifest::Dependencies& modDeps = pBundle->requiredModules();
	for (Poco::OSP::BundleManifest::Dependencies::const_iterator itModDep = modDeps.begin(); itModDep != modDeps.end(); ++itModDep)
	{
		if (itModDep != modDeps.begin()) ostr << ",";
		ostr
			<< "{"
			<< "\"symbolicName\":" << Utility::jsonize(itModDep->symbolicName) << ","
			<< "\"versions\":" << Utility::jsonize(itModDep->versions.toString())
			<< "}";
	}

	ostr
		<< "]"
		<< "}"
		<< "}";
}


void BundleRequestHandler::dependingBundles(Poco::OSP::Bundle::Ptr pBundle, BundleVec& dependingBundles, bool runningOnly)
{
	BundleVec bundles;
	context()->listBundles(bundles);
	for (BundleVec::const_iterator it = bundles.begin(); it != bundles.end(); ++it)
	{
		if (!runningOnly || (*it)->isStarted())
		{
			const Poco::OSP::BundleManifest::Dependencies& deps = (*it)->requiredBundles();
			for (Poco::OSP::BundleManifest::Dependencies::const_iterator itDep = deps.begin(); itDep != deps.end(); ++itDep)
			{
				if (itDep->symbolicName == pBundle->symbolicName())
				{
					dependingBundles.push_back(*it);
					break;
				}
			}
		}
	}
}


Poco::Net::HTTPRequestHandler* BundleRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new BundleRequestHandler(context());
}


} } } // namespace IoT::Web::BundleAdmin
