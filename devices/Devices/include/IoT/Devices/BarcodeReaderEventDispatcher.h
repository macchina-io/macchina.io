//
// BarcodeReaderEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_BarcodeReaderEventDispatcher_INCLUDED
#define IoT_Devices_BarcodeReaderEventDispatcher_INCLUDED


#include "IoT/Devices/BarcodeReaderRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class BarcodeReaderEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	BarcodeReaderEventDispatcher(BarcodeReaderRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a BarcodeReaderEventDispatcher.

	virtual ~BarcodeReaderEventDispatcher();
		/// Destroys the BarcodeReaderEventDispatcher.

	void event__barcodeRead(const void* pSender, const IoT::Devices::BarcodeReadEvent& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__barcodeReadImpl(const std::string& subscriberURI, const IoT::Devices::BarcodeReadEvent& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	BarcodeReaderRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BarcodeReaderEventDispatcher::remoting__typeId() const
{
	return IBarcodeReader::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BarcodeReaderEventDispatcher_INCLUDED

