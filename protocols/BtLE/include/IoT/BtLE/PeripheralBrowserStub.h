//
// PeripheralBrowserStub.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralBrowserStub_INCLUDED
#define IoT_BtLE_PeripheralBrowserStub_INCLUDED


#include "IoT/BtLE/PeripheralBrowserRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserStub: public IoT::BtLE::PeripheralBrowserRemoteObject
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	typedef Poco::AutoPtr<PeripheralBrowserStub> Ptr;

	PeripheralBrowserStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject);
		/// Creates a PeripheralBrowserStub.

	virtual ~PeripheralBrowserStub();
		/// Destroys the PeripheralBrowserStub.

	virtual void browse(int seconds);
		/// Browses for peripherals, for the given number of seconds.
		///
		/// Any peripherals found will be reported through the peripheralFound
		/// event. Scanning for peripherals will be done asynchronously, therefore
		/// this method returns immediately.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual std::string serviceForPeripheral(const std::string& address);
		/// Finds or creates and registers with the Service Registry, if necessary, 
		/// a Peripheral (remote) object for the device with the given address.
		///
		/// Returns the service name of the Peripheral service.
		/// The actual service instance can be obtained via the
		/// Service Registry.

protected:
	void event__browseComplete();

	void event__peripheralFound(const IoT::BtLE::PeripheralInfo& data);

private:
	Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> _pServiceObject;
};


inline void PeripheralBrowserStub::browse(int seconds)
{
	_pServiceObject->browse(seconds);
}


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralBrowserStub::remoting__typeId() const
{
	return IPeripheralBrowser::remoting__typeId();
}


inline std::string PeripheralBrowserStub::serviceForPeripheral(const std::string& address)
{
	return _pServiceObject->serviceForPeripheral(address);
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralBrowserStub_INCLUDED

