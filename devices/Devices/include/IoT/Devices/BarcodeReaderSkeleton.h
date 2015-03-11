//
// BarcodeReaderSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BarcodeReaderSkeleton_INCLUDED
#define IoT_Devices_BarcodeReaderSkeleton_INCLUDED


#include "IoT/Devices/BarcodeReaderRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class BarcodeReaderSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	BarcodeReaderSkeleton();
		/// Creates a BarcodeReaderSkeleton.

	virtual ~BarcodeReaderSkeleton();
		/// Destroys a BarcodeReaderSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BarcodeReaderSkeleton::remoting__typeId() const
{
	return IBarcodeReader::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BarcodeReaderSkeleton_INCLUDED

