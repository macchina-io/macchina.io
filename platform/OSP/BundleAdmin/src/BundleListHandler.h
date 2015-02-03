//
// BundleListHandler.h
//
// $Id: //poco/1.4/OSP/BundleAdmin/src/BundleListHandler.h#2 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
