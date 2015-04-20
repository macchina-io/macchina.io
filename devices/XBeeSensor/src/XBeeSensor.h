//
// XBeeSensor.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeSensor_INCLUDED
#define IoT_XBee_XBeeSensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/XBee/IXBeeNode.h"
#include "Poco/Util/Timer.h"


namespace IoT {
namespace XBee {
namespace Sensor {


class XBeeSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, XBeeSensor>
{
public:
	struct Params
	{
		std::string id;
			/// The ID (64-bit device address) of the sensor, as a hexadecimal string.

		int analogChannel;
			/// The analog channel to read the measurement from.
			
		std::string physicalQuantity;
			/// The physical quantity measured by the sensor.
			
		std::string physicalUnit;
			/// The physical unit of the measurements obtained by the sensor.
	};
	
	XBeeSensor(IXBeeNode::Ptr pXBeeNode, Params params);
		/// Creates a XBeeSensor.

	~XBeeSensor();
		/// Destroys the XBeeSensor.
	
	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	void update(double value);
	virtual void onIOSampleReceived(const IOSample& ioSample) = 0;

protected:
	IXBeeNode::Ptr _pXBeeNode;
	std::string _id;
	int _analogChannel;
	bool _ready;
	double _value;
	double _valueChangedDelta;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double> > _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _symbolicName;
	Poco::Any _name;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
};


class XBeeTemperatureSensor: public XBeeSensor
{
public:
	XBeeTemperatureSensor(IXBeeNode::Ptr pXBeeNode, Params params);
		/// Creates the XBeeTemperatureSensor.

	~XBeeTemperatureSensor();
		/// Destroys the XBeeTemperatureSensor.
		
protected:
	void onIOSampleReceived(const IOSample& ioSample);
};


class XBeeHumiditySensor: public XBeeSensor
{
public:
	XBeeHumiditySensor(IXBeeNode::Ptr pXBeeNode, Params params);
		/// Creates the XBeeTemperatureSensor.

	~XBeeHumiditySensor();
		/// Destroys the XBeeTemperatureSensor.
		
protected:
	void onIOSampleReceived(const IOSample& ioSample);
};


class XBeeLightSensor: public XBeeSensor
{
public:
	XBeeLightSensor(IXBeeNode::Ptr pXBeeNode, Params params);
		/// Creates the XBeeTemperatureSensor.

	~XBeeLightSensor();
		/// Destroys the XBeeTemperatureSensor.
		
protected:
	void onIOSampleReceived(const IOSample& ioSample);
};


} } } // namespace IoT::XBee::Sensor


#endif // IoT_XBee_XBeeSensor_INCLUDED
