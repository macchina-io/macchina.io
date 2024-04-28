//
// CompositeEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CompositeEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CompositeEventDispatcher_INCLUDED
#define IoT_Devices_CompositeEventDispatcher_INCLUDED


#include "IoT/Devices/IComposite.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class CompositeEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// A composite device consists of one or
	/// more sub devices or device fragments.
	///
	/// Composites are used to build hierarchies
	/// of devices, also known as device trees.
	/// This is intended to represent the hierarchical
	/// structure of a more complex device.
	///
	/// For example, for an electric vehicle, the
	/// (simplified) device tree may look like:
	///
	///     / (root)
	///      Battery/
	///       Voltage
	///       Temperature
	///       ChargeLevel
	///      Motor/
	///        Switch
	///        PowerUsage
	///        RPM
	///        Temperature
	///        ...    
	///      ...
	///
	/// The DeviceTree class can be used to conveniently
	/// find a device in the tree.
{
public:
	CompositeEventDispatcher(IComposite* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a CompositeEventDispatcher.

	virtual ~CompositeEventDispatcher();
		/// Destroys the CompositeEventDispatcher.

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	IComposite* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CompositeEventDispatcher::remoting__typeId() const
{
	return IComposite::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CompositeEventDispatcher_INCLUDED

