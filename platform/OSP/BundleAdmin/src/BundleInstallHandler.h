//
// BundleInstallHandler.h
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleAdmin_BundleInstallHandler_INCLUDED
#define BundleAdmin_BundleInstallHandler_INCLUDED


#include "RequestHandler.h"


class BundleInstallHandler: public RequestHandler
	/// The handler for installing and upgrading bundles.
{
public:
	BundleInstallHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the BundleListHandler.

	~BundleInstallHandler();
		/// Destroys the BundleListHandler.
		
	void run();
	
protected:
	std::string bundlePath(const std::string& symbolicName);
};


#endif // BundleAdmin_BundleInstallHandler_INCLUDED
