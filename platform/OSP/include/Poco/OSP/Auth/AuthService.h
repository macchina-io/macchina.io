//
// AuthService.h
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
// SPDX-License-Identifier: GPL-3.0-only
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
	using Ptr = Poco::AutoPtr<AuthService>;

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

	virtual bool authorize(const std::string& userName, const std::string& roleOrScope, const std::string& permission) const = 0;
		/// Checks if a user has a specific permission within the given role or scope.
		///
		/// If roleOrScope is empty, the result is the same as the two-argument version.
		/// If a non-empty roleOrScope is given, the method checks whether the user
		/// has the given permission within that given role or scope.
		///
		/// Role or scope is defined by the specific implementation. 
		///
		/// Returns true if the user specified by userName has the specified permission.

	virtual bool userExists(const std::string& userName) const = 0;
		/// Checks if a user has exists.
		///
		/// Returns true if the user specified by userName exists, otherwise false.

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
};


} } } // namespace Poco::OSP::Auth


#endif // OSP_Auth_AuthService_INCLUDED
