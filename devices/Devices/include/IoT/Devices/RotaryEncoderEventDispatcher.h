//
// RotaryEncoderEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_RotaryEncoderEventDispatcher_INCLUDED
#define IoT_Devices_RotaryEncoderEventDispatcher_INCLUDED


#include "IoT/Devices/RotaryEncoderRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class RotaryEncoderEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// A rotary encoder with an optional push button, based
	/// on the Counter interface.
{
public:
	RotaryEncoderEventDispatcher(RotaryEncoderRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a RotaryEncoderEventDispatcher.

	virtual ~RotaryEncoderEventDispatcher();
		/// Destroys the RotaryEncoderEventDispatcher.

	void event__buttonStateChanged(const void* pSender, const bool& data);

	void event__countChanged(const void* pSender, const Poco::Int32& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__buttonStateChangedImpl(const std::string& subscriberURI, const bool& data);

	void event__countChangedImpl(const std::string& subscriberURI, const Poco::Int32& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	RotaryEncoderRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& RotaryEncoderEventDispatcher::remoting__typeId() const
{
	return IRotaryEncoder::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_RotaryEncoderEventDispatcher_INCLUDED

