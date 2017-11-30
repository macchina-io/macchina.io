//
// ITrigger.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ITrigger
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ITrigger_INCLUDED
#define IoT_Devices_ITrigger_INCLUDED


#include "IoT/Devices/IBooleanSensor.h"
#include "IoT/Devices/Trigger.h"


namespace IoT {
namespace Devices {


class ITrigger: public IoT::Devices::IBooleanSensor
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
	typedef Poco::AutoPtr<ITrigger> Ptr;

	ITrigger();
		/// Creates a ITrigger.

	virtual ~ITrigger();
		/// Destroys the ITrigger.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ITrigger_INCLUDED

