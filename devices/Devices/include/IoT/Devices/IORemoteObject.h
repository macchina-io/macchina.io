//
// IORemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IORemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IORemoteObject_INCLUDED
#define IoT_Devices_IORemoteObject_INCLUDED


#include "IoT/Devices/IIO.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IORemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IIO
	/// The interface for general purpose input/output (GPIO)
	/// ports.
	///
	/// This class represents a single GPIO pin. 
	/// Mapping to physical pins is configured when setting up 
	/// the specific IO implementation class, typically using a 
	/// configuration file.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose a string property named "direction" that takes the
	/// values "in" and "out".
{
public:
	typedef Poco::AutoPtr<IORemoteObject> Ptr;

	IORemoteObject();
		/// Creates a IORemoteObject.

	virtual ~IORemoteObject();
		/// Destroys the IORemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& IORemoteObject::remoting__typeId() const
{
	return IIO::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IORemoteObject_INCLUDED

