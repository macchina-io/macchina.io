//
// TokenValidator.h
//
// Library: OSP/Web
// Package: Web
// Module:  TokenValidator
//
// Definition of the TokenValidator class.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Web_TokenValidator_INCLUDED
#define OSP_Web_TokenValidator_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Service.h"


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API TokenValidator: public Poco::OSP::Service
	/// TokenValidator is an optional service that is used
	/// by the WebServerDispatcher to validate bearer tokens
	/// and obtain the associated user name.
{
public:
	using Ptr = Poco::AutoPtr<TokenValidator>;

	virtual bool validateToken(const std::string& token, std::string& username, std::string& scope) = 0;
		/// Validates the given bearer token.
		///
		/// If valid, returns true and the associated username and scope.
		/// If invalid, returns false, leaving the username and scope unchanged.
		///
		/// The format of the token (e.g., JWT) and method of validation
		/// is left to the implementation.

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_TokenValidator_INCLUDED
