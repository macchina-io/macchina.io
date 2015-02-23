//
// TriggerEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_TriggerEventDispatcher_INCLUDED
#define IoT_Devices_TriggerEventDispatcher_INCLUDED


#include "IoT/Devices/TriggerRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class TriggerEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for triggers, such as
	/// push buttons or motion detectors.
	///
	/// In addition to the methods defined in this interface,
	/// a Trigger implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	TriggerEventDispatcher(TriggerRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a TriggerEventDispatcher.

	virtual ~TriggerEventDispatcher();
		/// Destroys the TriggerEventDispatcher.

	void event__stateChanged(const void* pSender, const bool& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const bool& data);

	static const std::string DEFAULT_NS;
	TriggerRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& TriggerEventDispatcher::remoting__typeId() const
{
	return ITrigger::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_TriggerEventDispatcher_INCLUDED

