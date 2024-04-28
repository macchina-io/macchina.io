//
// WebEventNotifierEventDispatcher.h
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebEvent_WebEventNotifierEventDispatcher_INCLUDED
#define IoT_WebEvent_WebEventNotifierEventDispatcher_INCLUDED


#include "IoT/WebEvent/IWebEventNotifier.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace WebEvent {


class WebEventNotifierEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// A simplified Remoting-capable interface to the
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	WebEventNotifierEventDispatcher(IWebEventNotifier* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a WebEventNotifierEventDispatcher.

	virtual ~WebEventNotifierEventDispatcher();
		/// Destroys the WebEventNotifierEventDispatcher.

	void event__event(const void* pSender, const IoT::WebEvent::EventNotification& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__eventImpl(const std::string& subscriberURI, const IoT::WebEvent::EventNotification& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	IWebEventNotifier* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WebEventNotifierEventDispatcher::remoting__typeId() const
{
	return IWebEventNotifier::remoting__typeId();
}


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_WebEventNotifierEventDispatcher_INCLUDED

