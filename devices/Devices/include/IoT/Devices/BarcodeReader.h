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


//@ serialize
struct BarcodeReadEvent
{
	std::string code;
		/// A textual representation of the scanned barcode.
		
	std::string type;
		/// Type of the scanned barcode, if reported by the device.
		///
		/// Should be left empty if the device does not report the
		/// type of the scanned barcode.
		///
		/// The following type names should be used:
		///
		///   - codabar
		///   - code11
		///   - ean-13
		///   - ean-8
		///   - upc-a
		///   - upc-e
		///   - code128
		///   - code39
		///   - code93
		///   - datamatrix
		///   - qrcode
};


//@ remote
class IoTDevices_API BarcodeReader: public Device
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	Poco::BasicEvent<const BarcodeReadEvent> barcodeRead;
		/// Fired when a barcode has been read.
		
	BarcodeReader();
		/// Creates the BarcodeReader.
		
	~BarcodeReader();
		/// Destroys the BarcodeReader.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_BarcodeReader_INCLUDED
