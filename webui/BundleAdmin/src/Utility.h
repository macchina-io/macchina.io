//
// Utility.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BundleAdmin_Utility_INCLUDED
#define BundleAdmin_Utility_INCLUDED


#include "Poco/Poco.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/Net/HTTPServerResponse.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


class Utility
	/// This class contains various utility functions used by server pages.
{
public:
	static bool isAuthenticated(Poco::OSP::Web::WebSession::Ptr pSession, Poco::Net::HTTPServerResponse& response);
		/// Checks if there is a valid session. 
		///
		/// Returns true if the session is valid.
		/// Returns false and sends the HTTP response with a 401 status if not.
	
	static std::string jsonize(const std::string& str);
		/// Creates a copy of str properly quoted and escaped for use in JSON.
};


} } } // namespace IoT::Web::BundleAdmin


#endif // BundleAdmin_Utility_INCLUDED
