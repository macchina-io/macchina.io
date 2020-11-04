//
// BundleInfoHandler.h
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleAdmin_BundleInfoHandler_INCLUDED
#define BundleAdmin_BundleInfoHandler_INCLUDED


#include "RequestHandler.h"
#include <vector>


class BundleInfoHandler: public RequestHandler
	/// The handler for the bundle information page.
{
public:
	BundleInfoHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the BundleInfoHandler.

	~BundleInfoHandler();
		/// Destroys the BundleInfoHandler.

	void run();

protected:
	using BundleVec = std::vector<Poco::OSP::Bundle::Ptr>;

	void dependencies(Poco::OSP::Bundle::Ptr pBundle);
	void modules(Poco::OSP::Bundle::Ptr pBundle);
	void provided(Poco::OSP::Bundle::Ptr pBundle);
	void actions(Poco::OSP::Bundle::Ptr pBundle);
	bool performAction(Poco::OSP::Bundle::Ptr pBundle, const std::string& action);
	void confirmUninstall(Poco::OSP::Bundle::Ptr pBundle);
	void confirmStop(Poco::OSP::Bundle::Ptr pBundle, const BundleVec& dependingBundles);
	void dependingBundles(Poco::OSP::Bundle::Ptr pBundle, BundleVec& dependingBundles);
};


#endif // BundleAdmin_BundleInfoHandler_INCLUDED
