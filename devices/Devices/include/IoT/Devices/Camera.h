//
// Camera.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  Camera
//
// Definition of the Camera interface.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Camera_INCLUDED
#define IoT_Devices_Camera_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


using ImageData = std::vector<char>;


//@ serialize
struct Image
{
	using Ptr = Poco::SharedPtr<Image>;

	int width = 0;
		/// Width of the image, in pixels (= number of columns).

	int height = 0;
		/// Height of the image, in pixels (= number of rows).

	std::string encoding;
		/// Encoding of the image. The meaning of the encoding
		/// string is defined by the implementation.

	Poco::SharedPtr<ImageData> image;
		/// Raw image data.

	int step = 0;
		/// Full row length in bytes. Only used for certain formats.
};


//@ remote
class IoTDevices_API Camera: public Device
	/// The base class for image sensors, also known as cameras.
{
public:
	Poco::BasicEvent<const Image::Ptr> imageCaptured;
		/// Fired when a new image has been captured.

	Camera();
		/// Creates the Camera.

	~Camera();
		/// Destroys the Camera.

	virtual Image::Ptr image() const = 0;
		/// Returns the most recently taken image, or a null pointer
		/// if no image is available.

	virtual bool ready() const = 0;
		/// Returns true if the camera is ready.

	virtual void capture() = 0;
		/// Capture an image.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Camera_INCLUDED
