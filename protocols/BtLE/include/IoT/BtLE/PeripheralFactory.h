//
// PeripheralFactory.h
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralFactory
//
// Definition of the PeripheralFactory class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralFactory_INCLUDED
#define IoT_BtLE_PeripheralFactory_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"


namespace IoT {
namespace BtLE {


class IoTBtLE_API PeripheralFactory: public Poco::OSP::Service
	/// A factory for Peripheral objects.
	///
	/// Given the address of a Bluetooth LE Peripheral device, the
	/// createPeripheral() method will create a Peripheral object
	/// representing that device.
	///
	/// This service is intended for use by implementations of
	/// specific Bluetooth LE devices that provide a high-level
	/// interface to the device's features, but need the Peripheral
	/// object to communicate with the actual device.
{
public:
	typedef Poco::AutoPtr<PeripheralFactory> Ptr;

	virtual Peripheral::Ptr createPeripheral(const std::string& address) = 0;
		/// Creates and returns a Peripheral object for the Peripheral with the
		/// given address (e.g., "C4:BE:84:72:C5:06").
		
	virtual ~PeripheralFactory();
		/// Destroys the PeripheralFactory.

	// Poco::OSP::Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
	
	static const std::string SERVICE_NAME;
		/// The service name of the PeripheralFactory.
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_PeripheralFactory_INCLUDED
