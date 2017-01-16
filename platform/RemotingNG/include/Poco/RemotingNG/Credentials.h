//
// Credentials.h
//
// $Id$
//
// Library: RemotingNG
// Package: Transport
// Module:  Credentials
//
// Definition of the Credentials class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_Credentials_INCLUDED
#define RemotingNG_Credentials_INCLUDED


#include "Poco/RemotingNG/AttributedObject.h"


namespace Poco {
namespace RemotingNG {


class RemotingNG_API Credentials: public AttributedObject
	/// This class contains credentials for authentication.
	///
	/// The content of a Credentials object depends upon a
	/// specific authentication mechanism and is implementation 
	/// specific.
	///
	/// In case of username/password credentials, a Credentials
	/// object would contain a "username" and a "password" attribute.
{
public:
	Credentials();
		/// Creates an empty Credentials object.

	Credentials(const Credentials& other);
		/// Creates a Credentials object by copying the attributes from another one.
		
	Credentials& operator = (const Credentials& other);
		/// Assigns the attributes from another Credentials object.
		
	~Credentials();
		/// Destroys the Credentials object.
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_Credentials_INCLUDED
