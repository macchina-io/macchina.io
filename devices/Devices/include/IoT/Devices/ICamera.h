//
// ICamera.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ICamera
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ICamera_INCLUDED
#define IoT_Devices_ICamera_INCLUDED


#include "IoT/Devices/Camera.h"
#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ICamera: public IoT::Devices::IDevice
	/// The base class for image sensors, also known as cameras.
{
public:
	typedef Poco::AutoPtr<ICamera> Ptr;

	ICamera();
		/// Creates a ICamera.

	virtual ~ICamera();
		/// Destroys the ICamera.

	virtual void capture() = 0;
		/// Capture an image.

	virtual Poco::SharedPtr < IoT::Devices::Image > image() const = 0;
		/// Returns the most recently taken image, or a null pointer
		/// if no image is available.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual bool ready() const = 0;
		/// Returns true if the camera is ready.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const Image::Ptr > imageCaptured;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ICamera_INCLUDED

