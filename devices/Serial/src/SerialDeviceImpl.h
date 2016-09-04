//
// SerialDeviceImpl.h
//
// $Id$
//
// Library: IoT/Serial
// Package: Serial
// Module:  SerialDevice
//
// Definition of the SerialDeviceImpl class.
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Serial_SerialDeviceImpl_INCLUDED
#define IoT_Serial_SerialDeviceImpl_INCLUDED


#include "Poco/Serial/SerialPort.h"
#include "IoT/Devices/SerialDevice.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace Serial {


class SerialDeviceImpl: public IoT::Devices::DeviceImpl<IoT::Devices::SerialDevice, SerialDeviceImpl>, public Poco::Runnable
	/// Default implementation for SerialDevice using the
	/// Poco::Serial::SerialPort class.
{
public:
	typedef Poco::AutoPtr<SerialDeviceImpl> Ptr;
	typedef Poco::SharedPtr<Poco::Serial::SerialPort> SerialPortPtr;

	SerialDeviceImpl(SerialPortPtr pSerialPort);
		/// Creates the SerialDeviceImpl using the given SerialPort object.
		
	~SerialDeviceImpl();
		/// Destroys the SerialDeviceImpl.
	
	// SerialDevice
	void reconfigure(int baudRate, const std::string& parameters, const std::string& flowControl);
	bool poll(double timeout);
	void setRTS(bool status);
	bool getRTS() const;
	void writeString(const std::string& data);
	std::string readString();
	std::string readLine(const std::string& delimiters, double timeout);
	void writeByte(Poco::UInt8 byte);
	Poco::UInt8 readByte();
	int available() const;
	
protected:
	Poco::Any getName(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getDevice(const std::string&) const;
	Poco::Any getBaudRate(const std::string&) const;
	Poco::Any getParameters(const std::string&) const;
	Poco::Any getFlowControl(const std::string&) const;
	Poco::Any getDelimiters(const std::string&) const;
	void setDelimiters(const std::string&, const Poco::Any& value);
	Poco::Any getTimeout(const std::string&) const;
	void setTimeout(const std::string&, const Poco::Any& value);

	bool getEvents(const std::string&) const;
	void setEvents(const std::string&, bool enable);
	
	void enableEvents();
	void disableEvents();
	
	bool eventsCancelled();
	
	void run();
	
	static const std::string NAME;
	static const std::string SYMBOLIC_NAME;
	static const std::string FLOW_NONE;
	static const std::string FLOW_RTSCTS;

private:
	SerialPortPtr _pSerialPort;
	std::string _delimiters;
	double _timeout;
	Poco::SharedPtr<Poco::Thread> _pThread;
	Poco::FastMutex _mutex;
	bool _cancelEvents;
};


} } // namespace IoT::Serial


#endif // IoT_Serial_SerialDeviceImpl_INCLUDED
