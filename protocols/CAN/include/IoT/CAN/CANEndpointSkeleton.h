//
// CANEndpointSkeleton.h
//
// Library: IoT/CAN
// Package: Generated
// Module:  CANEndpointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_CANEndpointSkeleton_INCLUDED
#define IoT_CAN_CANEndpointSkeleton_INCLUDED


#include "IoT/CAN/CANEndpointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace CAN {


class CANEndpointSkeleton: public Poco::RemotingNG::Skeleton
	/// The CANEndpoint is used to receive and send CAN and CAN-FD frames.
{
public:
	CANEndpointSkeleton();
		/// Creates a CANEndpointSkeleton.

	virtual ~CANEndpointSkeleton();
		/// Destroys a CANEndpointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CANEndpointSkeleton::remoting__typeId() const
{
	return ICANEndpoint::remoting__typeId();
}


} // namespace CAN
} // namespace IoT


#endif // IoT_CAN_CANEndpointSkeleton_INCLUDED

