//
// GyroscopeRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GyroscopeRemoteObject_INCLUDED
#define IoT_Devices_GyroscopeRemoteObject_INCLUDED


#include "IoT/Devices/IGyroscope.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class GyroscopeRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IGyroscope
	/// The interface for three-axis Gyroscopes.
{
public:
	typedef Poco::AutoPtr<GyroscopeRemoteObject> Ptr;

	GyroscopeRemoteObject();
		/// Creates a GyroscopeRemoteObject.

	virtual ~GyroscopeRemoteObject();
		/// Destroys the GyroscopeRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& GyroscopeRemoteObject::remoting__typeId() const
{
	return IGyroscope::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GyroscopeRemoteObject_INCLUDED

