//
// XBeeNodeSkeleton.h
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNodeSkeleton_INCLUDED
#define IoT_XBee_XBeeNodeSkeleton_INCLUDED


#include "IoT/XBee/XBeeNodeRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace XBee {


class XBeeNodeSkeleton: public Poco::RemotingNG::Skeleton
	/// This class provides a high-level interface to a Digi XBee device
	/// using the Digi XBee API frame-based protocol. This class can be
	/// used with all XBee devices supporting the XBee API frame-based
	/// protocol, including ZigBee devices. Actually supported methods
	/// and events are depending on the kind of XBee device, e.g., an
	/// 802.15.4 module won't support ZigBee-specific API frames, and
	/// vice-versa. Please refer to the XBee product manual for detailed
	/// information about the API.
{
public:
	XBeeNodeSkeleton();
		/// Creates a XBeeNodeSkeleton.

	virtual ~XBeeNodeSkeleton();
		/// Destroys a XBeeNodeSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& XBeeNodeSkeleton::remoting__typeId() const
{
	return IXBeeNode::remoting__typeId();
}


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_XBeeNodeSkeleton_INCLUDED

