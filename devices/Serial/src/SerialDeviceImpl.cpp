//
// SerialDeviceImpl.cpp
//
// $Id$
//
// Library: IoT/Serial
// Package: Serial
// Module:  SerialDevice
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Serial/SerialDeviceImpl.h"
#include <cmath>


namespace IoT {
namespace Serial {


const std::string SerialDeviceImpl::NAME("Serial Port");
const std::string SerialDeviceImpl::SYMBOLIC_NAME("io.macchina.serialport");
const std::string SerialDeviceImpl::FLOW_NONE("none");
const std::string SerialDeviceImpl::FLOW_RTSCTS("rtscts");


SerialDeviceImpl::SerialDeviceImpl(SerialPortPtr pSerialPort):
	_pSerialPort(pSerialPort),
	_timeout(0.0),
	_cancelEvents(false)
{
	addProperty("symbolicName", &SerialDeviceImpl::getSymbolicName);
	addProperty("name", &SerialDeviceImpl::getName);
	addProperty("baudRate", &SerialDeviceImpl::getBaudRate);
	addProperty("parameters", &SerialDeviceImpl::getParameters);
	addProperty("device", &SerialDeviceImpl::getDevice);
	addProperty("flowControl", &SerialDeviceImpl::getFlowControl);
	addProperty("delimiters", &SerialDeviceImpl::getDelimiters, &SerialDeviceImpl::setDelimiters);
	addProperty("timeout", &SerialDeviceImpl::getTimeout, &SerialDeviceImpl::setTimeout);
	
	addFeature("events", &SerialDeviceImpl::getEvents, &SerialDeviceImpl::setEvents);
}

	
SerialDeviceImpl::~SerialDeviceImpl()
{
	disableEvents();
}


void SerialDeviceImpl::reconfigure(int baudRate, const std::string& parameters, const std::string& flowControl)
{
	bool eventsMode = !_pThread.isNull();
	if (eventsMode) disableEvents();

	_pSerialPort->close();
	_pSerialPort->open(_pSerialPort->device(), baudRate, parameters, flowControl == "rtscts" ? SerialPort::FLOW_RTSCTS : SerialPort::FLOW_NONE);

	if (eventsMode) enableEvents();
}


bool SerialDeviceImpl::poll(double timeout)
{
	Poco::Timespan ts(static_cast<long>(std::floor(timeout)), (timeout - std::floor(timeout))*1000000);
	return _pSerialPort->poll(ts);
}


void SerialDeviceImpl::setRTS(bool status)
{
	_pSerialPort->setRTS(status);
}


bool SerialDeviceImpl::getRTS() const
{
	return _pSerialPort->getRTS();
}


void SerialDeviceImpl::writeString(const std::string& data)
{
	_pSerialPort->write(data);
}


std::string SerialDeviceImpl::readString()
{
	std::string data;
	_pSerialPort->read(data);
	return data;
}


std::string SerialDeviceImpl::readLine(const std::string& delimiters, double timeout)
{
	Poco::Timespan ts(static_cast<long>(std::floor(timeout)), (timeout - std::floor(timeout))*1000000);
	std::string line;
	while (_pSerialPort->poll(ts))
	{
		char ch = static_cast<char>(_pSerialPort->read());
		if (delimiters.find(ch) != std::string::npos) break;
		line += ch;
	}
	return line;
}


void SerialDeviceImpl::writeByte(Poco::UInt8 byte)
{
	char ch = static_cast<char>(byte);
	_pSerialPort->write(&ch, 1);
}


Poco::UInt8 SerialDeviceImpl::readByte()
{
	return static_cast<Poco::UInt8>(_pSerialPort->read());
}


int SerialDeviceImpl::available() const
{
	return static_cast<int>(_pSerialPort->available());
}


Poco::Any SerialDeviceImpl::getName(const std::string&) const
{
	return NAME;
}


Poco::Any SerialDeviceImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any SerialDeviceImpl::getDevice(const std::string&) const
{
	return _pSerialPort->device();
}


Poco::Any SerialDeviceImpl::getBaudRate(const std::string&) const
{
	return _pSerialPort->baudRate();
}


Poco::Any SerialDeviceImpl::getParameters(const std::string&) const
{
	return _pSerialPort->parameters();
}


Poco::Any SerialDeviceImpl::getFlowControl(const std::string&) const
{
	return _pSerialPort->flowControl() == SerialPort::FLOW_NONE ? FLOW_NONE : FLOW_RTSCTS;
}


Poco::Any SerialDeviceImpl::getDelimiters(const std::string&) const
{
	return _delimiters;
}


void SerialDeviceImpl::setDelimiters(const std::string&, const Poco::Any& value)
{
	_delimiters = Poco::AnyCast<std::string>(value);
}


Poco::Any SerialDeviceImpl::getTimeout(const std::string&) const
{
	return _timeout;
}


void SerialDeviceImpl::setTimeout(const std::string&, const Poco::Any& value)
{
	_timeout = Poco::AnyCast<double>(value);
}


bool SerialDeviceImpl::getEvents(const std::string&) const
{
	return !_pThread.isNull();
}


void SerialDeviceImpl::setEvents(const std::string&, bool enable)
{
	if (enable && !_pThread)
	{
		enableEvents();
	}
	else if (!enable && _pThread)
	{
		disableEvents();
	}
}


void SerialDeviceImpl::enableEvents()
{
	if (!_pThread)
	{	
		_cancelEvents = false;
		_pThread = new Poco::Thread("Serial Port" + _pSerialPort->device());
		_pThread->start(*this);
	}
}


void SerialDeviceImpl::disableEvents()
{
	if (_pThread)
	{
		{
			Poco::FastMutex::ScopedLock lock(_mutex);
			_cancelEvents = true;
		}
		_pThread->join();
		_pThread = 0;
	}
}


bool SerialDeviceImpl::eventsCancelled()
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	return _cancelEvents;
}


void SerialDeviceImpl::run()
{
	while (!eventsCancelled())
	{
		try
		{
			if (_pSerialPort->poll(250000))
			{
				std::string line = readLine(_delimiters, _timeout);
				lineReceived(line);
			}
		}
		catch (Poco::Exception&)
		{
		}
	}
}


} } // namespace IoT::Serial
