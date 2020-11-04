//
// VoltageSensorImpl.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Legato_VoltageSensorImpl_INCLUDED
#define IoT_Legato_VoltageSensorImpl_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/Timestamp.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"


namespace IoT {
namespace Legato {


class VoltageSensorImpl: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, VoltageSensorImpl>
	/// This sensor provides the module input power supply voltage,
	/// based on the "cm ips read" command.
{
public:
	VoltageSensorImpl(const std::string& cmPath);
		/// Creates a VoltageSensorImpl.

	~VoltageSensorImpl();
		/// Destroys the VoltageSensorImpl.

	// Sensor
	double value() const;
	bool ready() const;

protected:
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	Poco::Any getDisplayValue(const std::string&) const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;
	static const std::string PHYSICAL_QUANTITY;

private:
	std::string _cmPath;
	mutable double _voltage;
	mutable Poco::Timestamp _lastMeasurement;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


} } // namespace IoT::Legato


#endif // IoT_Legato_VoltageSensorImpl_INCLUDED
