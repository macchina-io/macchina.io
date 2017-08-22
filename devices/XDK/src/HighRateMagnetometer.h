//
// HighRateMagnetometer.h
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XDK_HighRateMagnetometer_INCLUDED
#define IoT_XDK_HighRateMagnetometer_INCLUDED


#include "IoT/Devices/Magnetometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {
namespace XDK {


class HighRateMagnetometer: public IoT::Devices::DeviceImpl<IoT::Devices::Magnetometer, HighRateMagnetometer>
{
public:
	typedef Poco::SharedPtr<HighRateMagnetometer> Ptr;

	HighRateMagnetometer(Peripheral::Ptr pPeripheral);
		/// Creates a HighRateMagnetometer.

	~HighRateMagnetometer();
		/// Destroys the HighRateMagnetometer.
	
	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::MagneticFieldStrength& fieldStrength);
		/// Updates the field strength.

	// Magnetometer
	IoT::Devices::MagneticFieldStrength fieldStrength() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void init();
	void enable(bool enabled);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	void onConnected();
	void onDisconnected();

protected:
	mutable Peripheral::Ptr _pPeripheral;
	bool _enabled;
	bool _ready;
	IoT::Devices::MagneticFieldStrength _fieldStrength;
	Poco::Any _deviceIdentifier;
};


} } } // namespace IoT::BtLE::XDK


#endif // IoT_XDK_HighRateMagnetometer_INCLUDED

