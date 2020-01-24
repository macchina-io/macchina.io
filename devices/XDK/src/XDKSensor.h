//
// XDKSensor.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XDK_XDKSensor_INCLUDED
#define IoT_XDK_XDKSensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XDK {


class XDKSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, XDKSensor>
{
public:
	using Ptr = Poco::SharedPtr<XDKSensor>;

	struct Params
	{
		std::string serviceUUID;
		std::string dataUUID;
		std::string physicalQuantity;
		std::string physicalUnit;
		long pollInterval;
	};

	XDKSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates a XDKSensor.

	~XDKSensor();
		/// Destroys the XDKSensor.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void init();
	void startPolling();
	void stopPolling();
	void enable(bool enabled);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	void update(double value);
	virtual void poll() = 0;
	void onConnected();
	void onDisconnected();

protected:
	Params _params;
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	Poco::Util::TimerTask::Ptr _pPollTask;
	BtLE::Characteristic _dataChar;
	bool _ready;
	bool _enabled;
	double _value;
	double _valueChangedDelta;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double>> _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;

	friend class PollTask;
};


class XDKTemperatureSensor: public XDKSensor
{
public:
	XDKTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the XDKTemperatureSensor.

	~XDKTemperatureSensor();
		/// Destroys the XDKTemperatureSensor.

protected:
	void poll();
};



class XDKHumiditySensor: public XDKSensor
{
public:
	XDKHumiditySensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the XDKHumiditySensor.

	~XDKHumiditySensor();
		/// Destroys the XDKHumiditySensor.

protected:
	void poll();
};


class XDKAirPressureSensor: public XDKSensor
{
public:
	XDKAirPressureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the XDKAirPressureSensor.

	~XDKAirPressureSensor();
		/// Destroys the XDKAirPressureSensor.

protected:
	void poll();
};


class XDKLightSensor: public XDKSensor
{
public:
	XDKLightSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the XDKLightSensor.

	~XDKLightSensor();
		/// Destroys the XDKLightSensor.

protected:
	void poll();
};


class XDKNoiseSensor: public XDKSensor
{
public:
	XDKNoiseSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the XDKNoiseSensor.

	~XDKNoiseSensor();
		/// Destroys the XDKNoiseSensor.

protected:
	void poll();
};


} } // namespace IoT::XDK


#endif // IoT_XDK_XDKSensor_INCLUDED
