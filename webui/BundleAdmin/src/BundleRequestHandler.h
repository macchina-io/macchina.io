//
// BundleRequestHandler.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BundleAdmin_BundleRequestHandler_INCLUDED
#define BundleAdmin_BundleRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include <vector>


namespace IoT {
namespace Web {
namespace BundleAdmin {


class BundleRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	BundleRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the BundleRequestHandler using the given bundle context.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	typedef std::vector<Poco::OSP::Bundle::Ptr> BundleVec;

	void dependingBundles(Poco::OSP::Bundle::Ptr pBundle, BundleVec& dependingBundles, bool runningOnly);
		/// Computes a list of bundles that depend on this bundle.

	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


class BundleRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::BundleAdmin


#endif // BundleAdmin_BundleRequestHandler_INCLUDED
