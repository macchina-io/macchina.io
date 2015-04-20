//
// XBeeNodeImpl.cpp
//
// $Id$
//
// Library: IoT/XBee
// Package: XBeeNode
// Module:  XBeeNode
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/XBeeNodeImpl.h"
#include "IoT/XBee/XBeeFrame.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"


namespace IoT {
namespace XBee {


XBeeNodeImpl::XBeeNodeImpl(Poco::SharedPtr<XBeePort> pXBeePort, int options):
	_pXBeePort(pXBeePort),
	_options(options),
	_stopped(false),
	_logger(Poco::Logger::get("IoT.XBeeNode"))
{
	start();
}

	
XBeeNodeImpl::~XBeeNodeImpl()
{
	stop();
}


void XBeeNodeImpl::sendFrame(const APIFrame& frame)
{
	XBeeFrame xbeeFrame(
		static_cast<XBeeFrame::FrameType>(frame.type),
		reinterpret_cast<const char*>(&frame.data[0]), frame.data.size());
		
	sendFrame(xbeeFrame);
}


void XBeeNodeImpl::sendCommand(const ATCommand& command)
{
	if (command.command.size() != 2) throw Poco::InvalidArgumentException("Invalid AT command", command.command);
	if (command.parameters.size() > 64) throw Poco::InvalidArgumentException("Too many parameter bytes");
	
	char buffer[80];
	Poco::MemoryOutputStream mostr(buffer, 80);
	Poco::BinaryWriter writer(mostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	
	writer << command.frameID;
	writer << command.command[0];
	writer << command.command[1];
	for (std::vector<Poco::UInt8>::const_iterator it = command.parameters.begin(); it != command.parameters.end(); ++it)
	{
		writer << *it;
	}

	XBeeFrame frame(XBeeFrame::XBEE_FRAME_AT_COMMAND, buffer, mostr.charsWritten());
	sendFrame(frame);
}


void XBeeNodeImpl::queueCommand(const ATCommand& command)
{
	if (command.command.size() != 2) throw Poco::InvalidArgumentException("Invalid AT command", command.command);
	if (command.parameters.size() > 64) throw Poco::InvalidArgumentException("Too many parameter bytes");
	
	char buffer[80];
	Poco::MemoryOutputStream mostr(buffer, 80);
	Poco::BinaryWriter writer(mostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	
	writer << command.frameID;
	writer << command.command[0];
	writer << command.command[1];
	for (std::vector<Poco::UInt8>::const_iterator it = command.parameters.begin(); it != command.parameters.end(); ++it)
	{
		writer << *it;
	}

	XBeeFrame frame(XBeeFrame::XBEE_FRAME_AT_COMMAND_QUEUE_PARAMETER_VALUE, buffer, mostr.charsWritten());
	sendFrame(frame);
}


void XBeeNodeImpl::sendRemoteCommand(const RemoteATCommand& command)
{
	if (command.command.size() != 2) throw Poco::InvalidArgumentException("Invalid AT command", command.command);
	if (command.parameters.size() > 64) throw Poco::InvalidArgumentException("Too many parameter bytes");
	
	char buffer[80];
	Poco::MemoryOutputStream mostr(buffer, 80);
	Poco::BinaryWriter writer(mostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	
	writer << command.frameID;
	
	Poco::UInt64 remoteAddress = 0;
	if (!command.deviceAddress.empty())
	{
		remoteAddress = Poco::NumberParser::parseHex64(command.deviceAddress);
	}
	writer << remoteAddress;
	
	Poco::UInt16 networkAddress = 0xFFFE;
	if (!command.networkAddress.empty())
	{
		networkAddress = static_cast<Poco::UInt16>(Poco::NumberParser::parseHex(command.networkAddress));
	}
	writer << networkAddress;
	
	writer << command.options;
	writer << command.command[0];
	writer << command.command[1];
	for (std::vector<Poco::UInt8>::const_iterator it = command.parameters.begin(); it != command.parameters.end(); ++it)
	{
		writer << *it;
	}

	XBeeFrame frame(XBeeFrame::XBEE_FRAME_REMOTE_AT_COMMAND_REQUEST, buffer, mostr.charsWritten());
	sendFrame(frame);
}


void XBeeNodeImpl::run()
{
	while (!_stopped)
	{
		try
		{
			if (_pXBeePort->poll(200000))
			{
				XBeeFrame frame;
				if (_pXBeePort->receiveFrame(frame, Poco::Timespan(200000)))
				{
					if (_options & XBEE_OPTION_ESCAPE_FRAMES)
					{
						frame.unescape();
					}
					if (_logger.debug())
					{
						_logger.debug(Poco::format("XBee frame received (type=0x%x, length=%z)", 
							static_cast<unsigned>(frame.type()), frame.frameSize()));
					}
					handleFrame(frame);
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
}


void XBeeNodeImpl::start()
{
	_stopped = false;
	_thread.start(*this);
}


void XBeeNodeImpl::stop()
{
	if (!_stopped)
	{
		_stopped = true;
		_thread.join();
	}
}


void XBeeNodeImpl::handleFrame(const XBeeFrame& frame)
{	
	APIFrame apiFrame;
	apiFrame.type = frame.type();
	apiFrame.data.assign(
		reinterpret_cast<const Poco::UInt8*>(frame.data()), 
		reinterpret_cast<const Poco::UInt8*>(frame.data()) + frame.dataSize());
	
	try
	{
		frameReceived(apiFrame);
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
	
	switch (frame.type())
	{
	case XBeeFrame::XBEE_FRAME_AT_COMMAND_RESPONSE:
		handleCommandResponse(frame);
		break;
	case XBeeFrame::XBEE_FRAME_REMOTE_AT_COMMAND_RESPONSE:
		handleRemoteCommandResponse(frame);
		break;
	case XBeeFrame::XBEE_FRAME_ZIGBEE_IO_DATA_SAMPLE_RX_INDICATOR:
		handleSampleRxIndicator(frame);
		break;
	default:
		break;
	}
}


void XBeeNodeImpl::handleCommandResponse(const XBeeFrame& frame)
{
	ATCommandResponse commandResponse;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	reader >> commandResponse.frameID;

	char command[2];
	reader >> command[0] >> command[1];
	commandResponse.command.assign(command, 2);

	reader >> commandResponse.status;

	for (std::size_t i = 4; i < frame.dataSize(); i++)
	{
		Poco::UInt8 byte;
		reader >> byte;
		commandResponse.data.push_back(byte);
	}

	commandResponseReceived(commandResponse);
}


void XBeeNodeImpl::handleRemoteCommandResponse(const XBeeFrame& frame)
{
	RemoteATCommandResponse commandResponse;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	reader >> commandResponse.frameID;
	
	Poco::UInt64 deviceAddress;
	reader >> deviceAddress;
	Poco::NumberFormatter::appendHex(commandResponse.deviceAddress, deviceAddress, 16);
	
	Poco::UInt16 networkAddress;
	reader >> networkAddress;
	Poco::NumberFormatter::appendHex(commandResponse.networkAddress, networkAddress, 4);
	
	char command[2];
	reader >> command[0] >> command[1];
	commandResponse.command.assign(command, 2);
	
	reader >> commandResponse.status;
	
	for (std::size_t i = 4; i < frame.dataSize(); i++)
	{
		Poco::UInt8 byte;
		reader >> byte;
		commandResponse.data.push_back(byte);
	}

	remoteCommandResponseReceived(commandResponse);
}


void XBeeNodeImpl::handleSampleRxIndicator(const XBeeFrame& frame)
{
	IOSample ioSample;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);

	Poco::UInt64 deviceAddress;
	reader >> deviceAddress;
	Poco::NumberFormatter::appendHex(ioSample.deviceAddress, deviceAddress, 16);
	
	Poco::UInt16 networkAddress;
	reader >> networkAddress;
	Poco::NumberFormatter::appendHex(ioSample.networkAddress, networkAddress, 4);
	
	reader >> ioSample.options >> ioSample.nSampleSets >> ioSample.digitalChannelMask >> ioSample.analogChannelMask;
	
	if (ioSample.digitalChannelMask)
	{
		reader >> ioSample.digitalSamples;
	}
	else
	{
		ioSample.digitalSamples = 0;
	}
	
	Poco::UInt8 analogChannelMask = ioSample.analogChannelMask;
	for (int i = 0; i < 8; i++)
	{
		if (analogChannelMask & 1)
		{
			Poco::Int16 sample;
			reader >> sample;
			ioSample.analogSamples.push_back(sample);
		}
		analogChannelMask >>= 1;
	}

	ioSampleReceived(ioSample);
}


void XBeeNodeImpl::sendFrame(XBeeFrame& frame)
{
	if (_logger.debug())
	{
		_logger.debug(Poco::format("Sending XBee frame (type=0x%x, length=%z)", 
			static_cast<unsigned>(frame.type()), frame.frameSize()));
	}

	if (_options & XBEE_OPTION_ESCAPE_FRAMES)
	{
		frame.escape();
	}

	Poco::FastMutex::ScopedLock lock(_mutex);

	_pXBeePort->sendFrame(frame);
}


} } // namespace IoT::XBee
