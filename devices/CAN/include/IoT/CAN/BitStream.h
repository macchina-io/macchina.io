//
// BitStream.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_BitStream_INCLUDED
#define IoT_CAN_BitStream_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include <cstdlib>


namespace IoT {
namespace CAN {


class IoTCANDevices_API BigEndianBitStream
	/// A BigEndianBitStream reads bits from a byte stream
	/// in big-endian byte order.
	///
	/// Given the following byte/bit sequence:
	///
	///    Byte:     0        1        2
	///          +--------+--------+--------+--- - -
	///          |    >432|10<     |        |
	///          +--------+--------+--------+--- - -
	///    Bit:   7      0 15     8 23    16 31
	///
	/// The 5-bit stream starting at offset 2 will be
	/// read in sequence 4-3-2-1-0.
{
public:
	BigEndianBitStream(const char* buffer, std::size_t offset, std::size_t length);
		/// Creates a BigEndianBitStream.

	~BigEndianBitStream();
		/// Destroys the BigEndianBitStream.

	char readBit();
		/// Returns the next bit from the bit stream.

	char readByte();
		/// Returns the next 8 bits from the bit stream.

	Poco::UInt32 readUnsigned();
		/// Reads an unsigned value.

	Poco::UInt32 readUnsigned(std::size_t length);
		/// Reads an unsigned value.

	Poco::Int32 readSigned();
		/// Reads a signed value.

	Poco::Int32 readSigned(std::size_t length);
		/// Reads a signed value.

	template <typename F>
	F readFloat()
		/// Reads a floating-point value (float or double).
	{
		F result;
		char* p = reinterpret_cast<char*>(&result);
#if defined(POCO_ARCH_BIG_ENDIAN)
		for (int i = 0; i < sizeof(F); i++)
		{
			*p++ = readByte();
		}
#else
		for (int i = sizeof(F) - 1; i >= 0; i--)
		{
			p[i] = readByte();
		}
#endif // POCO_ARCH_BIG_ENDIAN
		return result;
	}

	std::size_t remaining() const;
		/// Returns the number of bits remaining.

private:
	const char* _buffer;
	std::size_t _byteOffset;
	std::size_t _bitOffset;
	std::size_t _length;
};


class IoTCANDevices_API LittleEndianBitStream
	/// A BigEndianBitStream reads bits from a byte stream
	/// in big-endian byte order.
	///
	/// Given the following byte/bit sequence:
	///
	///    Byte:     0        1        2
	///          +--------+--------+--------+--- - -
	///          |543210< |    >876|
	///          +--------+--------+--------+--- - -
	///    Bit:   7      0 15     8 23    16 31
	///
	/// The 9-bit stream starting at offset 2 will be
	/// read in sequence 0-1-2-3-4-5-6-7-8.
{
public:
	LittleEndianBitStream(const char* buffer, std::size_t offset, std::size_t length);
		/// Creates a LittleEndianBitStream.

	~LittleEndianBitStream();
		/// Destroys the LittleEndianBitStream.

	char readBit();
		/// Returns the next bit from the bit stream.

	char readByte();
		/// Returns the next 8 bits from the bit stream.

	Poco::UInt32 readUnsigned();
		/// Reads an unsigned value.

	Poco::UInt32 readUnsigned(std::size_t length);
		/// Reads an unsigned value.

	Poco::Int32 readSigned();
		/// Reads a signed value.

	Poco::Int32 readSigned(std::size_t length);
		/// Reads a signed value.

	template <typename F>
	F readFloat()
		/// Reads a floating-point value (float or double).
	{
		F result;
		char* p = reinterpret_cast<char*>(&result);
#if defined(POCO_ARCH_BIG_ENDIAN)
		for (int i = sizeof(F) - 1; i >= 0; i--)
		{
			p[i] = readByte();
		}
#else
		for (int i = 0; i < sizeof(F); i++)
		{
			*p++ = readByte();
		}
#endif // POCO_ARCH_BIG_ENDIAN
		return result;
	}

	std::size_t remaining() const;
		/// Returns the number of bits remaining.

private:
	const char* _buffer;
	std::size_t _byteOffset;
	std::size_t _bitOffset;
	std::size_t _length;
};


//
// inlines
//
inline char BigEndianBitStream::readBit()
{
	poco_assert (_length > 0);

	char bit = (_buffer[_byteOffset] >> _bitOffset) & 0x01;
	if (_bitOffset == 0)
	{
		_bitOffset = 7;
		_byteOffset++;
	}
	else
	{
		_bitOffset--;
	}
	_length--;

	return bit;
}


inline char BigEndianBitStream::readByte()
{
	return static_cast<char>(readUnsigned(8));
}


inline Poco::UInt32 BigEndianBitStream::readUnsigned()
{
	return readUnsigned(_length);
}


inline Poco::Int32 BigEndianBitStream::readSigned()
{
	return readSigned(_length);
}


inline std::size_t BigEndianBitStream::remaining() const
{
	return _length;
}


inline char LittleEndianBitStream::readBit()
{
	poco_assert (_length > 0);

	char bit = (_buffer[_byteOffset] >> _bitOffset) & 0x01;
	if (_bitOffset == 7)
	{
		_bitOffset = 0;
		_byteOffset++;
	}
	else
	{
		_bitOffset++;
	}
	_length--;

	return bit;
}


inline char LittleEndianBitStream::readByte()
{
	return static_cast<char>(readUnsigned(8));
}


inline Poco::UInt32 LittleEndianBitStream::readUnsigned()
{
	return readUnsigned(_length);
}


inline Poco::Int32 LittleEndianBitStream::readSigned()
{
	return readSigned(_length);
}


inline std::size_t LittleEndianBitStream::remaining() const
{
	return _length;
}


} } // namespace IoT::CAN


#endif // IoT_CAN_BitStream_INCLUDED
