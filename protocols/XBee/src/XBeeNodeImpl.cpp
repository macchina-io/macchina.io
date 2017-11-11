//
// XBeeNodeImpl.cpp
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


namespace 
{
	void serializeDeviceAddress(Poco::BinaryWriter& writer, const std::string addr)
	{
		Poco::UInt64 deviceAddress = 0;
		if (!addr.empty())
		{
			deviceAddress = Poco::NumberParser::parseHex64(addr);
		}
		writer << deviceAddress;
	}
	
	void serializeNetworkAddress(Poco::BinaryWriter& writer, const std::string addr)
	{
		Poco::UInt16 networkAddress = 0xFFFE;
		if (!addr.empty())
		{
			networkAddress = static_cast<Poco::UInt16>(Poco::NumberParser::parseHex(addr));
		}
		writer << networkAddress;
	}
	
	void serializeData(Poco::BinaryWriter& writer, const std::vector<Poco::UInt8>& data)
	{
		for (std::vector<Poco::UInt8>::const_iterator it = data.begin(); it != data.end(); ++it)
		{
			writer << *it;
		}
	}
	
	void deserializeDeviceAddress(Poco::BinaryReader& reader, std::string& addr)
	{
		Poco::UInt64 deviceAddress;
		reader >> deviceAddress;
		addr.clear();
		Poco::NumberFormatter::appendHex(addr, deviceAddress, 16);
	}

	void deserializeNetworkAddress(Poco::BinaryReader& reader, std::string& addr)
	{
		Poco::UInt16 networkAddress;
		reader >> networkAddress;
		addr.clear();
		Poco::NumberFormatter::appendHex(addr, networkAddress, 4);
	}
	
	void deserializeData(Poco::BinaryReader& reader, std::size_t size, std::vector<Poco::UInt8>& data)
	{
		data.clear();
		for (std::size_t i = 0; i < size; i++)
		{
			Poco::UInt8 byte;
			reader >> byte;
			data.push_back(byte);
		}
	}
}


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
	serializeData(writer, command.parameters);

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
	serializeData(writer, command.parameters);

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
	serializeDeviceAddress(writer, command.deviceAddress);
	serializeNetworkAddress(writer, command.networkAddress);
	writer << command.options;
	writer << command.command[0];
	writer << command.command[1];
	serializeData(writer, command.parameters);

	XBeeFrame frame(XBeeFrame::XBEE_FRAME_REMOTE_AT_COMMAND_REQUEST, buffer, mostr.charsWritten());
	sendFrame(frame);
}


void XBeeNodeImpl::sendTransmitRequest(const TransmitRequest& request)
{
	if (request.payload.size() > XBEE_MAX_PAYLOAD_SIZE) throw Poco::InvalidArgumentException("Payload too large");
	
	XBeeFrame::FrameType frameType;

	char buffer[256];
	Poco::MemoryOutputStream mostr(buffer, 256);
	Poco::BinaryWriter writer(mostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	
	writer << request.frameID;
	if (request.deviceOrNetworkAddress.size() > 4)
	{
		frameType = XBeeFrame::XBEE_FRAME_TRANSMIT_REQUEST_64BIT_ADDRESS;
		serializeDeviceAddress(writer, request.deviceOrNetworkAddress);
	}
	else
	{
		frameType = XBeeFrame::XBEE_FRAME_TRANSMIT_REQUEST_16BIT_ADDRESS;
		serializeDeviceAddress(writer, request.deviceOrNetworkAddress);
	}
	writer << request.options;
	serializeData(writer, request.payload);

	XBeeFrame frame(frameType, buffer, mostr.charsWritten());
	sendFrame(frame);	
}


void XBeeNodeImpl::sendZigBeeTransmitRequest(const ZigBeeTransmitRequest& request)
{
	if (request.payload.size() > XBEE_MAX_PAYLOAD_SIZE) throw Poco::InvalidArgumentException("Payload too large");
	
	char buffer[256];
	Poco::MemoryOutputStream mostr(buffer, 256);
	Poco::BinaryWriter writer(mostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	
	writer << request.frameID;
	serializeDeviceAddress(writer, request.deviceAddress);
	serializeNetworkAddress(writer, request.networkAddress);
	writer << request.broadcastRadius;
	writer << request.options;
	serializeData(writer, request.payload);

	XBeeFrame frame(XBeeFrame::XBEE_FRAME_ZIGBEE_TRANSMIT_REQUEST, buffer, mostr.charsWritten());
	sendFrame(frame);	
}


void XBeeNodeImpl::sendExplicitAddressingZigBeeTransmitRequest(const ExplicitAddressingZigBeeTransmitRequest& request)
{
	if (request.payload.size() > XBEE_MAX_PAYLOAD_SIZE) throw Poco::InvalidArgumentException("Payload too large");
	
	char buffer[256];
	Poco::MemoryOutputStream mostr(buffer, 256);
	Poco::BinaryWriter writer(mostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	
	writer << request.frameID;
	serializeDeviceAddress(writer, request.deviceAddress);
	serializeNetworkAddress(writer, request.networkAddress);
	writer << request.sourceEndpoint;
	writer << request.destinationEndpoint;
	writer << request.clusterID;
	writer << request.profileID;
	writer << request.broadcastRadius;
	writer << request.options;
	serializeData(writer, request.payload);

	XBeeFrame frame(XBeeFrame::XBEE_FRAME_ZIGBEE_TRANSMIT_REQUEST, buffer, mostr.charsWritten());
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
	case XBeeFrame::XBEE_FRAME_TRANSMIT_STATUS:
		handleTransmitStatusReceived(frame);
		break;
	case XBeeFrame::XBEE_FRAME_RECEIVE_PACKET_64BIT_ADDRESS:
	case XBeeFrame::XBEE_FRAME_RECEIVE_PACKET_16BIT_ADDRESS:
		handlePacketReceived(frame);
		break;
	case XBeeFrame::XBEE_FRAME_RECEIVE_PACKET_64BIT_ADDRESS_IO:
	case XBeeFrame::XBEE_FRAME_RECEIVE_PACKET_16BIT_ADDRESS_IO:
		handleIODataReceived(frame);
		break;
	case XBeeFrame::XBEE_FRAME_ZIGBEE_TRANSMIT_STATUS:
		handleZigBeeTransmitStatusReceived(frame);
		break;
	case XBeeFrame::XBEE_FRAME_ZIGBEE_RECEIVE_PACKET:
		handleZigBeePacketReceived(frame);
		break;
	case XBeeFrame::XBEE_FRAME_ZIGBEE_EXPLICIT_RX_INDICATOR:
		handleExplicitAddressingZigBeePacketReceived(frame);
		break;
	case XBeeFrame::XBEE_FRAME_MODEM_STATUS:
		handleModemStatus(frame);
		break;
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


void XBeeNodeImpl::handleTransmitStatusReceived(const XBeeFrame& frame)
{
	TransmitStatus transmitStatus;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	reader 
		>> transmitStatus.frameID 
		>> transmitStatus.status;
	transmitStatusReceived(transmitStatus);
}


void XBeeNodeImpl::handlePacketReceived(const XBeeFrame& frame)
{
	ReceivePacket receivePacket;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	if (frame.type() == XBeeFrame::XBEE_FRAME_RECEIVE_PACKET_64BIT_ADDRESS)
	{
		deserializeDeviceAddress(reader, receivePacket.deviceOrNetworkAddress);
	}
	else
	{
		deserializeNetworkAddress(reader, receivePacket.deviceOrNetworkAddress);
	}
	
	reader 
		>> receivePacket.rssi 
		>> receivePacket.options;
	deserializeData(reader, reader.available(), receivePacket.payload);

	packetReceived(receivePacket);
}


void XBeeNodeImpl::handleIODataReceived(const XBeeFrame& frame)
{
	ReceivePacket receivePacket;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	if (frame.type() == XBeeFrame::XBEE_FRAME_RECEIVE_PACKET_64BIT_ADDRESS_IO)
	{
		deserializeDeviceAddress(reader, receivePacket.deviceOrNetworkAddress);
	}
	else
	{
		deserializeNetworkAddress(reader, receivePacket.deviceOrNetworkAddress);
	}
	
	reader 
		>> receivePacket.rssi 
		>> receivePacket.options;
	deserializeData(reader, reader.available(), receivePacket.payload);

	ioDataReceived(receivePacket);
}


void XBeeNodeImpl::handleZigBeeTransmitStatusReceived(const XBeeFrame& frame)
{
	ZigBeeTransmitStatus transmitStatus;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	reader >> transmitStatus.frameID;
	deserializeNetworkAddress(reader, transmitStatus.networkAddress);
	reader 
		>> transmitStatus.deliveryStatus 
		>> transmitStatus.discoveryStatus;

	zigBeeTransmitStatusReceived(transmitStatus);
}


void XBeeNodeImpl::handleZigBeePacketReceived(const XBeeFrame& frame)
{
	ZigBeeReceivePacket receivePacket;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	deserializeDeviceAddress(reader, receivePacket.deviceAddress);
	deserializeNetworkAddress(reader, receivePacket.networkAddress);
	reader >> receivePacket.options;
	deserializeData(reader, reader.available(), receivePacket.payload);

	zigBeePacketReceived(receivePacket);
}


void XBeeNodeImpl::handleExplicitAddressingZigBeePacketReceived(const XBeeFrame& frame)
{
	ExplicitAddressingZigBeeReceivePacket receivePacket;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	deserializeDeviceAddress(reader, receivePacket.deviceAddress);
	deserializeNetworkAddress(reader, receivePacket.networkAddress);
	reader 
		>> receivePacket.sourceEndpoint 
		>> receivePacket.destinationEndpoint 
		>> receivePacket.clusterID 
		>> receivePacket.profileID 
		>> receivePacket.options;
	deserializeData(reader, reader.available(), receivePacket.payload);

	explicitAddressingZigBeePacketReceived(receivePacket);
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
	deserializeData(reader, frame.dataSize() - 4, commandResponse.data);

	commandResponseReceived(commandResponse);
}


void XBeeNodeImpl::handleRemoteCommandResponse(const XBeeFrame& frame)
{
	RemoteATCommandResponse commandResponse;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	
	reader >> commandResponse.frameID;
	deserializeDeviceAddress(reader, commandResponse.deviceAddress);
	deserializeNetworkAddress(reader, commandResponse.networkAddress);
	
	char command[2];
	reader >> command[0] >> command[1];
	commandResponse.command.assign(command, 2);
	
	reader >> commandResponse.status;
	deserializeData(reader, frame.dataSize() - 14, commandResponse.data);

	remoteCommandResponseReceived(commandResponse);
}


void XBeeNodeImpl::handleSampleRxIndicator(const XBeeFrame& frame)
{
	IOSample ioSample;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);

	deserializeDeviceAddress(reader, ioSample.deviceAddress);
	deserializeNetworkAddress(reader, ioSample.networkAddress);
	
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


void XBeeNodeImpl::handleSensorRead(const XBeeFrame& frame)
{
	SensorRead sensorRead;
	Poco::MemoryInputStream mistr(frame.data(), frame.dataSize());
	Poco::BinaryReader reader(mistr, Poco::BinaryReader::NETWORK_BYTE_ORDER);

	deserializeDeviceAddress(reader, sensorRead.deviceAddress);
	deserializeNetworkAddress(reader, sensorRead.networkAddress);	
	reader >> sensorRead.options >> sensorRead.sensor;

	for (int i = 0; i < 4; i++)
	{
		Poco::Int16 sample;
		reader >> sample;
		sensorRead.analogSamples.push_back(sample);
	}
	
	reader >> sensorRead.temperature;
	
	sensorReadReceived(sensorRead);
}


void XBeeNodeImpl::handleModemStatus(const XBeeFrame& frame)
{
	ModemStatus modemStatus;

	if (frame.dataSize() > 0)
	{
		modemStatus.status = static_cast<Poco::UInt8>(*frame.data());
		modemStatusReceived(modemStatus);
	}
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
