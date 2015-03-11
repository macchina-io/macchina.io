//
// BarcodeReader.h
//
// $Id$
//
// Library: IoT/Devices
// Package: Devices
// Module:  BarcodeReader
//
// Definition of the BarcodeReader interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BarcodeReader_INCLUDED
#define IoT_Devices_BarcodeReader_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API BarcodeReader: public Device
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	Poco::BasicEvent<const std::string> barcodeRead;
		/// Fired when a barcode has been read.
		
	BarcodeReader();
		/// Creates the BarcodeReader.
		
	~BarcodeReader();
		/// Destroys the BarcodeReader.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_BarcodeReader_INCLUDED
