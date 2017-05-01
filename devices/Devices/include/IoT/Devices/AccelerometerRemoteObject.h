//
// AccelerometerRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_AccelerometerRemoteObject_INCLUDED
#define IoT_Devices_AccelerometerRemoteObject_INCLUDED


#include "IoT/Devices/IAccelerometer.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class AccelerometerRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IAccelerometer
	/// The interface for three-axis Accelerometers.
{
public:
	typedef Poco::AutoPtr<AccelerometerRemoteObject> Ptr;

	AccelerometerRemoteObject();
		/// Creates a AccelerometerRemoteObject.

	virtual ~AccelerometerRemoteObject();
		/// Destroys the AccelerometerRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& AccelerometerRemoteObject::remoting__typeId() const
{
	return IAccelerometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_AccelerometerRemoteObject_INCLUDED

