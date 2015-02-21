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
#include "Utility.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


BundleActionsRequestHandler::BundleActionsRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void BundleActionsRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
}


Poco::Net::HTTPRequestHandler* BundleActionsRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new BundleActionsRequestHandler(context());
}


} } } // namespace IoT::Web::BundleAdmin
