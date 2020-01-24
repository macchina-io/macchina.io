//
// HighRateGyroscope.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XDK_HighRateGyroscope_INCLUDED
#define IoT_XDK_HighRateGyroscope_INCLUDED


#include "IoT/Devices/Gyroscope.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XDK {


class HighRateGyroscope: public IoT::Devices::DeviceImpl<IoT::Devices::Gyroscope, HighRateGyroscope>
{
public:
	using Ptr = Poco::SharedPtr<HighRateGyroscope>;

	HighRateGyroscope(BtLE::Peripheral::Ptr pPeripheral);
		/// Creates a HighRateGyroscope.

	~HighRateGyroscope();
		/// Destroys the HighRateGyroscope.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::Rotation& rotation);
		/// Updates the Rotation.

	// Gyroscope
	IoT::Devices::Rotation rotation() const;

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
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	bool _enabled;
	bool _ready;
	IoT::Devices::Rotation _rotation;
	Poco::Any _deviceIdentifier;
};


} } // namespace IoT::XDK


#endif // IoT_XDK_HighRateGyroscope_INCLUDED
