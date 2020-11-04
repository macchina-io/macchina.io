//
// CANFDFrame.cpp
//
// Library: IoT/CAN
// Package: CANFrame
// Module:  CANEndpoint
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/CANFDFrame.h"
#include <algorithm>


namespace IoT {
namespace CAN {


CANFDFrame::CANFDFrame():
	_id(0),
	_flags(0)
{
}


CANFDFrame::CANFDFrame(ID id, Flags flags, const Payload& payload):
	_id(id),
	_flags(flags),
	_payload(payload)
{
	poco_assert (payload.size() <= MAX_PAYLOAD_SIZE);
}


CANFDFrame::CANFDFrame(ID id, Flags flags, Length length, const char* payload):
	_id(id),
	_flags(flags),
	_payload(payload, payload + length)
{
	poco_assert (length <= _payload.size());
}


CANFDFrame::CANFDFrame(const CANFDFrame& frame):
	_id(frame._id),
	_flags(frame._flags),
	_payload(frame._payload)
{
}


CANFDFrame::~CANFDFrame()
{
}


void CANFDFrame::assign(const CANFDFrame& frame)
{
	CANFDFrame tmp(frame);
	swap(tmp);
}


void CANFDFrame::assign(ID id, Flags flags, Length length, const char* payload)
{
	CANFDFrame tmp(id, flags, length, payload);
	swap(tmp);
}


void CANFDFrame::assign(ID id, Flags flags, const Payload& payload)
{
	CANFDFrame tmp(id, flags, payload);
	swap(tmp);
}


CANFDFrame& CANFDFrame::operator = (const CANFDFrame& frame)
{
	CANFDFrame tmp(frame);
	swap(tmp);
	return *this;
}


void CANFDFrame::swap(CANFDFrame& other)
{
	std::swap(_id, other._id);
	std::swap(_flags, other._flags);
	std::swap(_payload, other._payload);
}


} } // namespace IoT::CAN
