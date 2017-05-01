//
// XBeeNodeRemoteObject.h
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNodeRemoteObject_INCLUDED
#define IoT_XBee_XBeeNodeRemoteObject_INCLUDED


#include "IoT/XBee/IXBeeNode.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XBee {


class XBeeNodeRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::XBee::IXBeeNode
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
	typedef Poco::AutoPtr<XBeeNodeRemoteObject> Ptr;

	XBeeNodeRemoteObject();
		/// Creates a XBeeNodeRemoteObject.

	virtual ~XBeeNodeRemoteObject();
		/// Destroys the XBeeNodeRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& XBeeNodeRemoteObject::remoting__typeId() const
{
	return IXBeeNode::remoting__typeId();
}


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_XBeeNodeRemoteObject_INCLUDED

