//
// TriggerRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_TriggerRemoteObject_INCLUDED
#define IoT_Devices_TriggerRemoteObject_INCLUDED


#include "IoT/Devices/ITrigger.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class TriggerRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::ITrigger
	/// The base class for triggers, such as
	/// push buttons or motion detectors.
	///
	/// In addition to the methods defined in this interface,
	/// a Trigger implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	typedef Poco::AutoPtr<TriggerRemoteObject> Ptr;

	TriggerRemoteObject();
		/// Creates a TriggerRemoteObject.

	virtual ~TriggerRemoteObject();
		/// Destroys the TriggerRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& TriggerRemoteObject::remoting__typeId() const
{
	return ITrigger::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_TriggerRemoteObject_INCLUDED

