//
// SerialPort_WIN32.h
//
// $Id: //poco/1.4/IO/Serial/include/Poco/IO/Serial/SerialPort_WIN32.h#2 $
//
// Library: IoT/Serial
// Package: Serial
// Module:  SerialPort
//
// Definition of the SerialPortImpl class for Windows (CE).
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Serial_SerialPort_WIN32_INCLUDED
#define IoT_Serial_SerialPort_WIN32_INCLUDED


#include "IoT/Serial/Serial.h"
#include "Poco/Logger.h"
#include "Poco/Timespan.h"
#include "Poco/UnWindows.h"
#include <cctype>


namespace IoT {
namespace Serial {


class IoTSerial_API SerialPortImpl
	/// Serial port implementation for Windows.
{
public:
	enum FlowControlImpl
	{
		FLOW_NONE,
		FLOW_RTSCTS
	};
	
	struct RS485ParamsImpl
	{
		enum RS485Flags
		{
			RS485_ENABLED         = (1 << 0),
				/// Enable RS-485 mode for serial port.
			RS485_RTS_ON_SEND     = (1 << 1),
				/// Set logical level for RTS pin equal to 1 when sending, 
				/// enabling the RS-485 driver.
			RS485_RTS_AFTER_SEND  = (1 << 2),
				/// Set logical level for RTS pin equal to 1 after sending,
				/// disabling the RS-485 driver.
			RS485_USE_GPIO        = (1 << 5)
				/// Use GPIO pin instead of RTS to enable/disable the
				/// RS-485 driver.
		};
		
		int flags;
			/// Flags to configure RS-485 mode.
		int delayRTSBeforeSend;
			/// RTS delay before send.
		int delayRTSAfterSend;
			/// RTS delay after send.
		int gpioPin;
			/// GPIO pin to use if RS485_USE_GPIO flag is set.
	};

	SerialPortImpl();		
	~SerialPortImpl();
		
	void openImpl(const std::string& device, int baudRate, const std::string& parameters, FlowControlImpl flowControl);		
	void closeImpl();
	bool isOpenImpl() const;
	
	void drainImpl();
	void configureRS485Impl(const RS485ParamsImpl& rs485Params);
	void setRTSImpl(bool status);
	bool getRTSImpl() const;
	int pollImpl(char* data, std::size_t size, const Poco::Timespan& timeout);
	int readImpl(char* data, std::size_t size);
	int writeImpl(const char* data, std::size_t size);

private:
	enum
	{
		CHARACTER_TIMEOUT = 2 // timeout for single characters in milliseconds
	};
	
	HANDLE _handle;
	bool _rtsState;
};


//
// inlines
//
inline bool SerialPortImpl::isOpenImpl() const
{
	return _handle != INVALID_HANDLE_VALUE;
}


} } // namespace IoT::Serial


#endif // IoT_Serial_SerialPort_WIN32_INCLUDED
