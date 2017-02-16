//
// PlainClientAuthenticator.h
//
// $Id: //poco/1.7/RemotingNG/TCP/include/Poco/RemotingNG/TCP/PlainClientAuthenticator.h#1 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  PlainClientAuthenticator
//
// Definition of the PlainClientAuthenticator class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_TCP_PlainClientAuthenticator_INCLUDED
#define RemotingNG_TCP_PlainClientAuthenticator_INCLUDED


#include "Poco/RemotingNG/TCP/ClientAuthenticator.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RemotingNGTCP_API PlainClientAuthenticator: public ClientAuthenticator
	/// A very simple ClientAuthenticator for username/password
	/// based plain-text authentication.
	///
	/// Since credentials are transferred in clear text, this
	/// should only be used over an encrypted transport.
{
public:
	typedef Poco::AutoPtr<PlainClientAuthenticator> Ptr;

	static const std::string PLAIN;
		/// The name of the mechanism is "PLAIN".
	
	PlainClientAuthenticator();
		/// Creates the PlainClientAuthenticator.
		
	~PlainClientAuthenticator();
		/// Destroys the PlainClientAuthenticator.
	
	// ClientAuthenticator
	std::string startAuthentication(Credentials& clientCredentials);
	bool continueAuthentication(const Credentials& serverCredentials, Credentials& clientCredentials);
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_PlainClientAuthenticator_INCLUDED
