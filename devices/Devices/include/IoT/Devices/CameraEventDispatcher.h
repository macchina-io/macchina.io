//
// CameraEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CameraEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_CameraEventDispatcher_INCLUDED
#define IoT_Devices_CameraEventDispatcher_INCLUDED


#include "IoT/Devices/CameraRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class CameraEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for image sensors, also known as cameras.
{
public:
	CameraEventDispatcher(CameraRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a CameraEventDispatcher.

	virtual ~CameraEventDispatcher();
		/// Destroys the CameraEventDispatcher.

	void event__imageCaptured(const void* pSender, const Poco::SharedPtr < IoT::Devices::Image >& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__imageCapturedImpl(const std::string& subscriberURI, const Poco::SharedPtr < IoT::Devices::Image >& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	CameraRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CameraEventDispatcher::remoting__typeId() const
{
	return ICamera::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CameraEventDispatcher_INCLUDED

