//
// CredentialsStore.h
//
// $Id: //poco/1.7/RemotingNG/TCP/include/Poco/RemotingNG/TCP/CredentialsStore.h#1 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  CredentialsStore
//
// Definition of the CredentialsStore class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_TCP_CredentialsStore_INCLUDED
#define RemotingNG_TCP_CredentialsStore_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/Credentials.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Random.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RemotingNGTCP_API CredentialsStore: public Poco::RefCountedObject
	/// This class holds authentication tokens and their
	/// associated credentials.
{
public:
	typedef Poco::AutoPtr<CredentialsStore> Ptr;
	typedef std::map<Poco::UInt64, Credentials> CredentialsMap;

	CredentialsStore();
		/// Creates a CredentialsStore.
		
	~CredentialsStore();
		/// Destroys the CredentialsStore.
		
	Poco::UInt64 addCredentials(const Credentials& creds);
		/// Adds the credentials and return a new authentication
		/// token representing them.
		
	const Credentials& getCredentials(Poco::UInt64 authToken) const;
		/// Returns the Credentials identified by the given
		/// authentication token.
		///
		/// Throws a Poco::NotFoundException if no Credentials
		/// are associated with the given authentication token.

protected:	
	Poco::UInt64 generateAuthToken();
	
private:
	Poco::Random _random;
	CredentialsMap _credentials;
	mutable Poco::FastMutex _mutex;
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_CredentialsStore_INCLUDED
