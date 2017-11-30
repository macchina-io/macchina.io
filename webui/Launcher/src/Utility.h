//
// Utility.h
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef Launcher_Utility_INCLUDED
#define Launcher_Utility_INCLUDED


#include "Poco/Poco.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <set>


namespace IoT {
namespace Web {
namespace Launcher {


class Utility
	/// This class contains various utility functions used by server pages.
{
public:
	static bool isAuthenticated(Poco::OSP::Web::WebSession::Ptr pSession, Poco::Net::HTTPServerResponse& response);
		/// Checks if there is a valid session. 
		///
		/// Returns true if the session is valid.
		/// Returns false and sends the HTTP response with a 401 status if not.
	
	static std::string htmlize(const std::string& str);
		/// Creates a copy of str with reserved HTML characters propery escaped.

	static std::string jsonize(const std::string& str);
		/// Creates a copy of str properly quoted and escaped for use in JSON.

	static std::string text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id);
		/// Returns a localized variant of the user interface text 
		/// with the given ID.
		
	static std::string text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1);
		/// Returns a localized variant of the user interface text 
		/// with the given ID. 
		///
		/// The text is treated as a format string for Poco::format(), used 
		/// with the given argument(s).

	static std::string text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1, const Poco::Any& arg2);
		/// Returns a localized variant of the user interface text 
		/// with the given ID. 
		///
		/// The text is treated as a format string for Poco::format(), used 
		/// with the given argument(s).

	static std::string text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1, const Poco::Any& arg2, const Poco::Any& arg3);
		/// Returns a localized variant of the user interface text 
		/// with the given ID. 
		///
		/// The text is treated as a format string for Poco::format(), used 
		/// with the given argument(s).

	static std::string text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1, const Poco::Any& arg2, const Poco::Any& arg3, const Poco::Any& arg4);
		/// Returns a localized variant of the user interface text 
		/// with the given ID. 
		///
		/// The text is treated as a format string for Poco::format(), used 
		/// with the given argument(s).
};


// Shortcut, since it's needed so often.
typedef Utility U;


} } } // namespace IoT::Web::Launcher


#endif // Launcher_Utility_INCLUDED
