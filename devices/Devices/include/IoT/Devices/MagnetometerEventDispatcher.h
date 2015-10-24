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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_MagnetometerEventDispatcher_INCLUDED
#define IoT_Devices_MagnetometerEventDispatcher_INCLUDED


#include "IoT/Devices/MagnetometerRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class MagnetometerEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for three-axis Magnetometers.
{
public:
	MagnetometerEventDispatcher(MagnetometerRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a MagnetometerEventDispatcher.

	virtual ~MagnetometerEventDispatcher();
		/// Destroys the MagnetometerEventDispatcher.

	void event__fieldStrengthChanged(const void* pSender, const IoT::Devices::MagneticFieldStrength& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__fieldStrengthChangedImpl(const std::string& subscriberURI, const IoT::Devices::MagneticFieldStrength& data);

	static const std::string DEFAULT_NS;
	MagnetometerRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& MagnetometerEventDispatcher::remoting__typeId() const
{
	return IMagnetometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_MagnetometerEventDispatcher_INCLUDED

