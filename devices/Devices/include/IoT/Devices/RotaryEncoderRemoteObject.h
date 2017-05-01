//
// RotaryEncoderRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_RotaryEncoderRemoteObject_INCLUDED
#define IoT_Devices_RotaryEncoderRemoteObject_INCLUDED


#include "IoT/Devices/IRotaryEncoder.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class RotaryEncoderRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IRotaryEncoder
	/// A rotary encoder with an optional push button.
{
public:
	typedef Poco::AutoPtr<RotaryEncoderRemoteObject> Ptr;

	RotaryEncoderRemoteObject();
		/// Creates a RotaryEncoderRemoteObject.

	virtual ~RotaryEncoderRemoteObject();
		/// Destroys the RotaryEncoderRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& RotaryEncoderRemoteObject::remoting__typeId() const
{
	return IRotaryEncoder::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_RotaryEncoderRemoteObject_INCLUDED

