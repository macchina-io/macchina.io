//
// GyroscopeEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_GyroscopeEventDispatcher_INCLUDED
#define IoT_Devices_GyroscopeEventDispatcher_INCLUDED


#include "IoT/Devices/IGyroscope.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class GyroscopeEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for three-axis Gyroscopes.
{
public:
	GyroscopeEventDispatcher(IGyroscope* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a GyroscopeEventDispatcher.

	virtual ~GyroscopeEventDispatcher();
		/// Destroys the GyroscopeEventDispatcher.

	void event__rotationChanged(const void* pSender, const IoT::Devices::Rotation& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__rotationChangedImpl(const std::string& subscriberURI, const IoT::Devices::Rotation& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	IGyroscope* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& GyroscopeEventDispatcher::remoting__typeId() const
{
	return IGyroscope::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GyroscopeEventDispatcher_INCLUDED

