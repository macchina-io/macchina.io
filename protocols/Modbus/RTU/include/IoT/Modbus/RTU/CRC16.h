//
// CRC16.h
//
// Library: IoT/Modbus/RTU
// Package: RTU
// Module:  CRC16
//
// Definition of the CRC16 class.
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_RTU_CRC16_INCLUDED
#define IoT_Modbus_RTU_CRC16_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "Poco/Types.h"


namespace IoT {
namespace Modbus {
namespace RTU {


class IoTModbus_API CRC16
	/// A utility class for computing a CRC16 checksum as used in 
	/// the Modbus RTU protocol.
{
public:
	CRC16() = default;
	~CRC16() = default;

	Poco::UInt16 update(Poco::UInt8 byte);
		/// Updates the CRC with an additional byte and returns
		/// the updated CRC.

	Poco::UInt16 checksum() const;
		/// Returns the computed checksum.

	void reset();
		/// Resets the CRC16 so it can be reused.

private:
	Poco::UInt16 _crc = 0xffff;

	CRC16(const CRC16&) = delete;
	CRC16& operator = (const CRC16&) = delete;
};


//
// inlines
//


inline Poco::UInt16 CRC16::checksum() const
{
	return _crc;
}


inline void CRC16::reset()
{
	_crc = 0xffff;
}


} } } // namespace IoT::Modbus::RTU


#endif // IoT_Modbus_RTU_CRC16_INCLUDED
