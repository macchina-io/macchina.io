//
// BusDecoder.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_BusDecoder_INCLUDED
#define IoT_CAN_BusDecoder_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include "IoT/CAN/SignalDecoder.h"
#include <map>


namespace IoT {
namespace CAN {


class IoTCANDevices_API BusDecoder
	/// A collection of SignalDecoder instances.
{
public:
	typedef std::multimap<Poco::UInt32, SignalDecoder::Ptr> SignalDecoders;

	BusDecoder();
		/// Creates the BusDecoder.

	~BusDecoder();
		/// Destroys the BusDecoder.

	void addSignalDecoder(Poco::UInt32 id, SignalDecoder::Ptr pDecoder);
		/// Adds the given SignalDecoder for the given CAN ID.

	void decodeFrame(const CANFDFrame& frame);
		/// Decodes the given CANFDFrame by invoking all decoders
		/// registered for the ID of the frame.

private:
	SignalDecoders _decoders;
};


} } // namespace IoT::CAN


#endif // IoT_CAN_BusDecoder_INCLUDED
