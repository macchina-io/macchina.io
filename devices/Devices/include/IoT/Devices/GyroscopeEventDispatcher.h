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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GyroscopeEventDispatcher_INCLUDED
#define IoT_Devices_GyroscopeEventDispatcher_INCLUDED


#include "IoT/Devices/GyroscopeRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class GyroscopeEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for three-axis Gyroscopes.
{
public:
	GyroscopeEventDispatcher(GyroscopeRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a GyroscopeEventDispatcher.

	virtual ~GyroscopeEventDispatcher();
		/// Destroys the GyroscopeEventDispatcher.

	void event__rotationChanged(const void* pSender, const IoT::Devices::Rotation& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__rotationChangedImpl(const std::string& subscriberURI, const IoT::Devices::Rotation& data);

	static const std::string DEFAULT_NS;
	GyroscopeRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& GyroscopeEventDispatcher::remoting__typeId() const
{
	return IGyroscope::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GyroscopeEventDispatcher_INCLUDED

