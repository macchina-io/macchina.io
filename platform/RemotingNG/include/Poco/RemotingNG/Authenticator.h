//
// Authenticator.h
//
// $Id$
//
// Library: RemotingNG
// Package: Transport
// Module:  Authenticator
//
// Definition of the Authenticator class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_Authenticator_INCLUDED
#define RemotingNG_Authenticator_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/Credentials.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace RemotingNG {


class RemotingNG_API Authenticator: public Poco::RefCountedObject
	/// The Authenticator interface is used for authenticating credentials. 
	///
	/// Authenticators are specific to a transport and external authentication 
	/// mechanism and must be implemented specifically for an application.
{
public:
	typedef Poco::AutoPtr<Authenticator> Ptr;

	Authenticator();
		/// Creates the Authenticator.

	virtual ~Authenticator();
		/// Destroys the Authenticator.
		
	virtual bool authenticate(const Credentials& credentials) = 0;
		/// Verifies that the given credentials are valid.
		///
		/// Returns true if the credentials are valid, otherwise false.
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_Authenticator_INCLUDED
