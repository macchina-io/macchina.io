//
// AuthService.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/Auth/AuthService.h#1 $
//
// Library: OSP
// Package: Auth
// Module:  AuthService
//
// Definition of the AuthService service interface class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Auth_AuthService_INCLUDED
#define OSP_Auth_AuthService_INCLUDED


#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace OSP {
namespace Auth {


class OSP_API AuthService: public Poco::OSP::Service
	/// The AuthService (authentication/authorization service) is used to
	/// authenticate users using a user name/credentials combination, and to
	/// assign certain permissions to users.
	///
	/// The specific format of user credentials is defined by the actual implementation
	/// of this service. In the simplest form, the credentials are a simple password.
	///
	/// Permissions are simple strings identifying the permissions a specific user has.
	/// The AuthService itself does not care about the syntax and format of permissions.
{
public:
	typedef Poco::AutoPtr<AuthService> Ptr;
	
	AuthService();
		/// Creates the AuthService.
	
	~AuthService();
		/// Destroys the AuthService.

	virtual bool authenticate(const std::string& userName, const std::string& credentials) const = 0;
		/// Checks if the userName and credentials combination is valid.
		///
		/// Returns true if the user specified by userName is known and the specified credentials
		/// confirm the identity of the user. Returns false otherwise.

	virtual bool authorize(const std::string& userName, const std::string& permission) const = 0;
		/// Checks if a user has a specific permission.
		///
		/// Returns true if the user specified by userName has the specified permission.

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
};


} } } // namespace Poco::OSP::Auth


#endif // OSP_Auth_AuthService_INCLUDED
