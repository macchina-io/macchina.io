//
// GenericBooleanSensor.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GenericBooleanSensor_INCLUDED
#define IoT_Devices_GenericBooleanSensor_INCLUDED


#include "IoT/Devices/BooleanSensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IoTDevices_API GenericBooleanSensor: public IoT::Devices::DeviceImpl<IoT::Devices::BooleanSensor, GenericBooleanSensor>
{
public:
	typedef Poco::SharedPtr<GenericBooleanSensor> Ptr;

	GenericBooleanSensor(const std::string& name, const std::string& symbolicName);
		/// Creates a BooleanSensor.

	~GenericBooleanSensor();
		/// Destroys the BooleanSensor.

	void update(bool state);
		/// Updates the sensor state.

	void enable(bool enabled);
		/// Enables or disables the counter.

	// BooleanSensor
	bool state() const;

	static const std::string TYPE;

protected:
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	std::string _name;
	std::string _symbolicName;
	bool _enabled;
	bool _state;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_GenericBooleanSensor_INCLUDED
