//
// WebEventNotifierSkeleton.h
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebEvent_WebEventNotifierSkeleton_INCLUDED
#define IoT_WebEvent_WebEventNotifierSkeleton_INCLUDED


#include "IoT/WebEvent/WebEventNotifierRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace WebEvent {


class WebEventNotifierSkeleton: public Poco::RemotingNG::Skeleton
	/// A simplified Remoting-capable interface to the 
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	WebEventNotifierSkeleton();
		/// Creates a WebEventNotifierSkeleton.

	virtual ~WebEventNotifierSkeleton();
		/// Destroys a WebEventNotifierSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WebEventNotifierSkeleton::remoting__typeId() const
{
	return IWebEventNotifier::remoting__typeId();
}


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_WebEventNotifierSkeleton_INCLUDED

