//
// BundleInfoHandler.h
//
// $Id: //poco/1.6/OSP/BundleAdmin/src/BundleInfoHandler.h#1 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
	typedef std::vector<Poco::OSP::Bundle::Ptr> BundleVec;
	
	void dependencies(Poco::OSP::Bundle::Ptr pBundle);
	void actions(Poco::OSP::Bundle::Ptr pBundle);
	bool performAction(Poco::OSP::Bundle::Ptr pBundle, const std::string& action);
	void confirmUninstall(Poco::OSP::Bundle::Ptr pBundle);
	void confirmStop(Poco::OSP::Bundle::Ptr pBundle, const BundleVec& dependingBundles);
	void dependingBundles(Poco::OSP::Bundle::Ptr pBundle, BundleVec& dependingBundles);
};


#endif // BundleAdmin_BundleInfoHandler_INCLUDED
