//
// IPeripheralBrowser.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheralBrowser
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_IPeripheralBrowser_INCLUDED
#define IoT_BtLE_IPeripheralBrowser_INCLUDED


#include "IoT/BtLE/PeripheralBrowser.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace BtLE {


class IPeripheralBrowser: public Poco::OSP::Service
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	typedef Poco::AutoPtr<IPeripheralBrowser> Ptr;

	IPeripheralBrowser();
		/// Creates a IPeripheralBrowser.

	virtual ~IPeripheralBrowser();
		/// Destroys the IPeripheralBrowser.

	virtual void browse(int seconds) = 0;
		/// Browses for peripherals, for the given number of seconds.
		///
		/// Any peripherals found will be reported through the peripheralFound
		/// event. Scanning for peripherals will be done asynchronously, therefore
		/// this method returns immediately.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual std::string serviceForPeripheral(const std::string& address) = 0;
		/// Finds or creates and registers with the Service Registry, if necessary, 
		/// a Peripheral (remote) object for the device with the given address.
		///
		/// Returns the service name of the Peripheral service.
		/// The actual service instance can be obtained via the
		/// Service Registry.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < void > browseComplete;
	Poco::BasicEvent < const PeripheralInfo > peripheralFound;
};


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_IPeripheralBrowser_INCLUDED

