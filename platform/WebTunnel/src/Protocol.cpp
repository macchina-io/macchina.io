//
// Protocol.cpp
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  Protocol
//
// Definition of the Protocol class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/Protocol.h"
#include "Poco/BinaryWriter.h"
#include "Poco/BinaryReader.h"
#include "Poco/MemoryStream.h"


namespace Poco {
namespace WebTunnel {


std::size_t Protocol::writeHeader(char* pBuffer, std::size_t bufferSize, Poco::UInt8 opcode, Poco::UInt8 flags, Poco::UInt16 channel, Poco::UInt16 portOrErrorCode)
{
	Poco::MemoryOutputStream mos(pBuffer, static_cast<std::streamsize>(bufferSize));
	Poco::BinaryWriter writer(mos, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	writer << opcode << flags << channel;
	switch (opcode)
	{
	case WT_OP_OPEN_REQUEST:
	case WT_OP_OPEN_FAULT:
	case WT_OP_ERROR:
		writer << portOrErrorCode;
		break;
	}
	return static_cast<std::size_t>(mos.charsWritten());
}


std::size_t Protocol::readHeader(const char* pBuffer, std::size_t bufferSize, Poco::UInt8& opcode, Poco::UInt8& flags, Poco::UInt16& channel, Poco::UInt16* pPortOrErrorCode)
{
	Poco::MemoryInputStream mis(pBuffer, static_cast<std::streamsize>(bufferSize));
	Poco::BinaryReader reader(mis, Poco::BinaryReader::NETWORK_BYTE_ORDER);
	reader >> opcode >> flags >> channel;
	if (pPortOrErrorCode)
	{
		switch (opcode)
		{
		case WT_OP_OPEN_REQUEST:
		case WT_OP_OPEN_FAULT:
		case WT_OP_ERROR:
			reader >> *pPortOrErrorCode;
			return 6;
		}
	}
	return 4;
}


} } // namespace Poco::WebTunnel
