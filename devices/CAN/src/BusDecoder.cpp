//
// BusDecoder.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/BusDecoder.h"


namespace IoT {
namespace CAN {


BusDecoder::BusDecoder()
{
}


BusDecoder::~BusDecoder()
{
}


void BusDecoder::addSignalDecoder(Poco::UInt32 id, SignalDecoder::Ptr pDecoder)
{
	_decoders.insert(SignalDecoders::value_type(id, pDecoder));
}


void BusDecoder::decodeFrame(const CANFDFrame& frame)
{
	SignalDecoders::iterator it = _decoders.find(frame.id());
	while (it != _decoders.end() && it->first == frame.id())
	{
		it->second->decode(frame);
		++it;
	}
}


} } // namespace IoT::CAN
