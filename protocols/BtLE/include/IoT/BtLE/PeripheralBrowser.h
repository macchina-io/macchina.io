//
// PeripheralBrowser.h
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralBrowser
//
// Definition of the PeripheralBrowser class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralBrowser_INCLUDED
#define IoT_BtLE_PeripheralBrowser_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace BtLE {


//@ serialize
struct PeripheralInfo
{
	std::string address;
		/// Bluetooth address of the peripheral, e.g., "C4:BE:84:72:C5:06".
		
	std::string name;
		/// Peripheral name.
};


//@ remote
class IoTBtLE_API PeripheralBrowser
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	typedef Poco::SharedPtr<PeripheralBrowser> Ptr;

	Poco::BasicEvent<const PeripheralInfo> peripheralFound;
		/// Fired when a peripheral has been found.
		
	Poco::BasicEvent<void> browseComplete;
		/// Fired when browsing has been completed.

	virtual void browse(int seconds) = 0;
		/// Browses for peripherals, for the given number of seconds.
		///
		/// Any peripherals found will be reported through the peripheralFound
		/// event. Scanning for peripherals will be done asynchronously, therefore
		/// this method returns immediately.
		
	virtual std::string serviceForPeripheral(const std::string& address) = 0;
		/// Finds or creates and registers with the Service Registry, if necessary, 
		/// a Peripheral (remote) object for the device with the given address.
		///
		/// Returns the service name of the Peripheral service.
		/// The actual service instance can be obtained via the
		/// Service Registry.
	
	virtual ~PeripheralBrowser();
		/// Destroys the PeripheralBrowser.
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_PeripheralBrowser_INCLUDED
