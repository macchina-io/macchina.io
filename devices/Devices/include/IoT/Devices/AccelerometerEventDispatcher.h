//
// AccelerometerEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_AccelerometerEventDispatcher_INCLUDED
#define IoT_Devices_AccelerometerEventDispatcher_INCLUDED


#include "IoT/Devices/AccelerometerRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class AccelerometerEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for three-axis Accelerometers.
{
public:
	AccelerometerEventDispatcher(AccelerometerRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a AccelerometerEventDispatcher.

	virtual ~AccelerometerEventDispatcher();
		/// Destroys the AccelerometerEventDispatcher.

	void event__accelerationChanged(const void* pSender, const IoT::Devices::Acceleration& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__accelerationChangedImpl(const std::string& subscriberURI, const IoT::Devices::Acceleration& data);

	static const std::string DEFAULT_NS;
	AccelerometerRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& AccelerometerEventDispatcher::remoting__typeId() const
{
	return IAccelerometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_AccelerometerEventDispatcher_INCLUDED

