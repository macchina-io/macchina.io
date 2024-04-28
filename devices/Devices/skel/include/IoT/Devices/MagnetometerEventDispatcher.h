//
// MagnetometerEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_MagnetometerEventDispatcher_INCLUDED
#define IoT_Devices_MagnetometerEventDispatcher_INCLUDED


#include "IoT/Devices/IMagnetometer.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class MagnetometerEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for three-axis Magnetometers.
{
public:
	MagnetometerEventDispatcher(IMagnetometer* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a MagnetometerEventDispatcher.

	virtual ~MagnetometerEventDispatcher();
		/// Destroys the MagnetometerEventDispatcher.

	void event__fieldStrengthChanged(const void* pSender, const IoT::Devices::MagneticFieldStrength& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__fieldStrengthChangedImpl(const std::string& subscriberURI, const IoT::Devices::MagneticFieldStrength& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	IMagnetometer* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& MagnetometerEventDispatcher::remoting__typeId() const
{
	return IMagnetometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_MagnetometerEventDispatcher_INCLUDED

