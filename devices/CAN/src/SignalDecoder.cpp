//
// SignalDecoder.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/SignalDecoder.h"


namespace IoT {
namespace CAN {


SignalDecoder::SignalDecoder()
{
}


SignalDecoder::~SignalDecoder()
{
}


BooleanSensorDecoder::BooleanSensorDecoder(BooleanSensor::Ptr pSensor, std::size_t offset):
	_pSensor(pSensor),
	_offset(offset)
{
}


void BooleanSensorDecoder::decode(const CANFDFrame& frame)
{
	std::size_t byteOffset = _offset/8;
	std::size_t bitOffset = _offset%8;
	bool bit = ((frame.payload()[byteOffset] >> bitOffset) & 0x01) ? true : false;
	_pSensor->update(bit);
}


} } // namespace IoT::CAN
