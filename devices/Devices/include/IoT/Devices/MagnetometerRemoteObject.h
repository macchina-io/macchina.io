//
// MagnetometerRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_MagnetometerRemoteObject_INCLUDED
#define IoT_Devices_MagnetometerRemoteObject_INCLUDED


#include "IoT/Devices/IMagnetometer.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class MagnetometerRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IMagnetometer
	/// The interface for three-axis Magnetometers.
{
public:
	typedef Poco::AutoPtr<MagnetometerRemoteObject> Ptr;

	MagnetometerRemoteObject();
		/// Creates a MagnetometerRemoteObject.

	virtual ~MagnetometerRemoteObject();
		/// Destroys the MagnetometerRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& MagnetometerRemoteObject::remoting__typeId() const
{
	return IMagnetometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_MagnetometerRemoteObject_INCLUDED

