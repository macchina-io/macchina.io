//
// CANFrame.cpp
//
// Library: IoT/CAN
// Package: CANFrame
// Module:  CANEndpoint
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/CAN/CANFrame.h"
#include <algorithm>


namespace IoT {
namespace CAN {


CANFrame::CANFrame():
	_id(0),
	_flags(0),
	_dlc(0)
{
	_payload.assign(0);
}


CANFrame::CANFrame(ID id, Flags flags, DLC dlc, const Payload& payload):
	_id(id),
	_flags(flags),
	_dlc(dlc),
	_payload(payload)
{
	poco_assert (dlc <= _payload.size());
}


CANFrame::CANFrame(ID id, Flags flags, DLC dlc, const char* payload):
	_id(id),
	_flags(flags),
	_dlc(dlc)
{
	poco_assert (dlc <= _payload.size());

	DLC i = 0;
	for (; payload && i < dlc; i++) _payload[i] = payload[i];
	for (; i < _payload.size(); i++) _payload[i] = 0;
}


CANFrame::CANFrame(const CANFrame& frame):
	_id(frame._id),
	_flags(frame._flags),
	_dlc(frame._dlc),
	_payload(frame._payload)
{
}


CANFrame::~CANFrame()
{
}


void CANFrame::assign(const CANFrame& frame)
{
	CANFrame tmp(frame);
	swap(tmp);
}


void CANFrame::assign(ID id, Flags flags, DLC dlc, const char* payload)
{
	CANFrame tmp(id, flags, dlc, payload);
	swap(tmp);
}


void CANFrame::assign(ID id, Flags flags, DLC dlc, const Payload& payload)
{
	CANFrame tmp(id, flags, dlc, payload);
	swap(tmp);
}


CANFrame& CANFrame::operator = (const CANFrame& frame)
{
	CANFrame tmp(frame);
	swap(tmp);
	return *this;
}


void CANFrame::swap(CANFrame& other)
{
	std::swap(_id, other._id);
	std::swap(_flags, other._flags);
	std::swap(_dlc, other._dlc);
	std::swap(_payload, other._payload);
}


} } // namespace IoT::CAN
