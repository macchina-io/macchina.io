//
// IOEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IOEventDispatcher_INCLUDED
#define IoT_Devices_IOEventDispatcher_INCLUDED


#include "IoT/Devices/IORemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class IOEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for general purpose input/output (GPIO)
	/// ports.
	///
	/// This class represents a single GPIO pin. 
	/// Mapping to physical pins is configured when setting up 
	/// the specific IO implementation class, typically using a 
	/// configuration file.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose a string property named "direction" that takes the
	/// values "in" and "out".
{
public:
	IOEventDispatcher(IORemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a IOEventDispatcher.

	virtual ~IOEventDispatcher();
		/// Destroys the IOEventDispatcher.

	void event__stateChanged(const void* pSender, const bool& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const bool& data);

	static const std::string DEFAULT_NS;
	IORemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& IOEventDispatcher::remoting__typeId() const
{
	return IIO::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IOEventDispatcher_INCLUDED

