//
// IOEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IOEventDispatcher_INCLUDED
#define IoT_Devices_IOEventDispatcher_INCLUDED


#include "IoT/Devices/IORemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class IOEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for general purpose input/output (GPIO)
	/// devices.
	///
	/// The IO class supports up to 32 logical pins. Each logical
	/// pin is mapped to a physical pin on the hardware. Logical
	/// pins are counted from 0 to 31. Mapping to physical pins
	/// is configured when setting up the IO implementation class,
	/// typically using a configuration file.
	///
	/// Implementations that support interrupt-capable input pins
	/// should expose an int property named "stateChangedEventMask"
	/// that allows enabling interrupts for specific pins, based
	/// on the given bit mask.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose int properties named "configureInputs" and
	/// "configureOutputs" that take a bit mask specifying affected pins.
{
public:
	IOEventDispatcher(IORemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a IOEventDispatcher.

	virtual ~IOEventDispatcher();
		/// Destroys the IOEventDispatcher.

	void event__stateChanged(const void* pSender, const Poco::UInt32& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const Poco::UInt32& data);

	static const std::string DEFAULT_NS;
	IORemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& IOEventDispatcher::remoting__typeId() const
{
	return IIO::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IOEventDispatcher_INCLUDED

