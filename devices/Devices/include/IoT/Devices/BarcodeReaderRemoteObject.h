//
// BarcodeReaderRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BarcodeReaderRemoteObject_INCLUDED
#define IoT_Devices_BarcodeReaderRemoteObject_INCLUDED


#include "IoT/Devices/IBarcodeReader.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class BarcodeReaderRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IBarcodeReader
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	typedef Poco::AutoPtr<BarcodeReaderRemoteObject> Ptr;

	BarcodeReaderRemoteObject();
		/// Creates a BarcodeReaderRemoteObject.

	virtual ~BarcodeReaderRemoteObject();
		/// Destroys the BarcodeReaderRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& BarcodeReaderRemoteObject::remoting__typeId() const
{
	return IBarcodeReader::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BarcodeReaderRemoteObject_INCLUDED

