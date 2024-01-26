//
// ScalarDatapointEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_ScalarDatapointEventDispatcher_INCLUDED
#define IoT_Devices_ScalarDatapointEventDispatcher_INCLUDED


#include "IoT/Devices/ScalarDatapointRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class ScalarDatapointEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// A scalar datapoint holding a single numeric (double) value.
	///
	/// In addition to the methods defined in this interface,
	/// a ScalarDatapoint implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the datapoint, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "Cel" for degree Celsius).
	///     This should use the "c/s" symbols from the Unified Code for Units of Measure
	///     (http://unitsofmeasure.org/ucum.html).
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	ScalarDatapointEventDispatcher(ScalarDatapointRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a ScalarDatapointEventDispatcher.

	virtual ~ScalarDatapointEventDispatcher();
		/// Destroys the ScalarDatapointEventDispatcher.

	void event__invalidated(const void* pSender);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const void* pSender, const double& data);

	void event__valueChanged(const void* pSender, const double& data);

	void event__valueUpdated(const void* pSender, const double& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__invalidatedImpl(const std::string& subscriberURI);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	void event__validatedImpl(const std::string& subscriberURI, const double& data);

	void event__valueChangedImpl(const std::string& subscriberURI, const double& data);

	void event__valueUpdatedImpl(const std::string& subscriberURI, const double& data);

	static const std::string DEFAULT_NS;
	ScalarDatapointRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ScalarDatapointEventDispatcher::remoting__typeId() const
{
	return IScalarDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ScalarDatapointEventDispatcher_INCLUDED

