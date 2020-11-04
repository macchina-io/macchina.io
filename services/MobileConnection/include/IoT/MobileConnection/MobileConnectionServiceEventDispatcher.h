//
// MobileConnectionServiceEventDispatcher.h
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  MobileConnectionServiceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_MobileConnection_MobileConnectionServiceEventDispatcher_INCLUDED
#define IoT_MobileConnection_MobileConnectionServiceEventDispatcher_INCLUDED


#include "IoT/MobileConnection/MobileConnectionServiceRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace MobileConnection {


class MobileConnectionServiceEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The MobileConnectionService interface is used to configure
	/// and establish a mobile data connection.
{
public:
	MobileConnectionServiceEventDispatcher(MobileConnectionServiceRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a MobileConnectionServiceEventDispatcher.

	virtual ~MobileConnectionServiceEventDispatcher();
		/// Destroys the MobileConnectionServiceEventDispatcher.

	void event__dataConnected(const void* pSender);

	void event__dataDisconnected(const void* pSender);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__dataConnectedImpl(const std::string& subscriberURI);

	void event__dataDisconnectedImpl(const std::string& subscriberURI);

	static const std::string DEFAULT_NS;
	MobileConnectionServiceRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& MobileConnectionServiceEventDispatcher::remoting__typeId() const
{
	return IMobileConnectionService::remoting__typeId();
}


} // namespace MobileConnection
} // namespace IoT


#endif // IoT_MobileConnection_MobileConnectionServiceEventDispatcher_INCLUDED

