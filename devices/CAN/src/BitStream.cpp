//
// BitStream.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/BitStream.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CAN {


BigEndianBitStream::BigEndianBitStream(const char* buffer, std::size_t offset, std::size_t length):
	_buffer(buffer),
	_byteOffset(offset/8),
	_bitOffset(offset%8),
	_length(length)
{
}


BigEndianBitStream::~BigEndianBitStream()
{
}


Poco::UInt32 BigEndianBitStream::readUnsigned(std::size_t length)
{
	poco_assert (length <= _length);

	Poco::UInt32 value(0);
	while (length-- > 0)
	{
		value <<= 1;
		value |= readBit();
	}
	return value;
}


Poco::Int32 BigEndianBitStream::readSigned(std::size_t length)
{
	poco_assert (length <= _length);

	Poco::Int32 value(readBit() ? 0xFFFFFFFF : 0); // sign-extend
	while (--length > 0)
	{
		value <<= 1;
		value |= readBit();
	}
	return value;
}


LittleEndianBitStream::LittleEndianBitStream(const char* buffer, std::size_t offset, std::size_t length):
	_buffer(buffer),
	_byteOffset(offset/8),
	_bitOffset(offset%8),
	_length(length)
{
}


LittleEndianBitStream::~LittleEndianBitStream()
{
}


Poco::UInt32 LittleEndianBitStream::readUnsigned(std::size_t length)
{
	poco_assert (length <= _length);

	int offset = 0;
	Poco::UInt32 value(0);
	while (length-- > 0)
	{
		value |= static_cast<Poco::UInt32>(readBit()) << offset++;
	}
	return value;
}


Poco::Int32 LittleEndianBitStream::readSigned(std::size_t length)
{
	poco_assert (length <= _length);

	int offset = 0;
	Poco::Int32 value(0);
	while (length-- > 1)
	{
		value |= static_cast<Poco::UInt32>(readBit()) << offset++;
	}
	value |= static_cast<Poco::UInt32>(readBit() ? 0xFFFFFFFF : 0) << offset;
	return value;
}



} } // namespace IoT::CAN
