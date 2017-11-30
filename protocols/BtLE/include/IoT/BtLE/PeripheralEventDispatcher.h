//
// PeripheralEventDispatcher.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralEventDispatcher_INCLUDED
#define IoT_BtLE_PeripheralEventDispatcher_INCLUDED


#include "IoT/BtLE/PeripheralRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace BtLE {


class PeripheralEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	PeripheralEventDispatcher(PeripheralRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a PeripheralEventDispatcher.

	virtual ~PeripheralEventDispatcher();
		/// Destroys the PeripheralEventDispatcher.

	void event__connected(const void* pSender);

	void event__disconnected(const void* pSender);

	void event__error(const void* pSender, const std::string& data);

	void event__indicationReceived(const void* pSender, const IoT::BtLE::Indication& data);

	void event__notificationReceived(const void* pSender, const IoT::BtLE::Notification& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__connectedImpl(const std::string& subscriberURI);

	void event__disconnectedImpl(const std::string& subscriberURI);

	void event__errorImpl(const std::string& subscriberURI, const std::string& data);

	void event__indicationReceivedImpl(const std::string& subscriberURI, const IoT::BtLE::Indication& data);

	void event__notificationReceivedImpl(const std::string& subscriberURI, const IoT::BtLE::Notification& data);

	static const std::string DEFAULT_NS;
	PeripheralRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralEventDispatcher::remoting__typeId() const
{
	return IPeripheral::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralEventDispatcher_INCLUDED

