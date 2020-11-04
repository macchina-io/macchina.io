//
// BundleListHandler.h
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleAdmin_BundleListHandler_INCLUDED
#define BundleAdmin_BundleListHandler_INCLUDED


#include "RequestHandler.h"


class BundleListHandler: public RequestHandler
	/// The handler for the bundle list.
{
public:
	BundleListHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the BundleListHandler.

	~BundleListHandler();
		/// Destroys the BundleListHandler.
		
	void run();
};


#endif // BundleAdmin_BundleListHandler_INCLUDED
