//
// CANFrame.h
//
// Library: IoT/CAN
// Package: CANFrame
// Module:  CANEndpoint
//
// Definition of the CANFrame class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_CANFrame_INCLUDED
#define IoT_CAN_CANFrame_INCLUDED


#include "IoT/CAN/CAN.h"
#include "Poco/Array.h"
#include "Poco/Exception.h"


namespace IoT {
namespace CAN {


//@ serialize
class CANFrame
	/// A CAN frame.
{
public:
	typedef Poco::UInt32 ID;
	typedef Poco::UInt8  Flags;
	typedef Poco::UInt8  DLC;
	typedef Poco::Array<char, 8> Payload;

	enum Flag
	{
		CAN_FLAG_NONE = 0, /// No flags set
		CAN_FLAG_IDE  = 1, /// CAN Identifier Extension bit (signalling extended frame format)
		CAN_FLAG_RTR  = 2, /// CAN Remote Transmission Request bit
		CAN_FLAG_SRR  = 4, /// CAN Substitute Remote Request bit (extended frame only, currently unused)
		CAN_FLAG_ERR  = 8  /// Error frame indicator
	};

	enum
	{
		MAX_PAYLOAD_SIZE = 8
	};

	CANFrame();
		/// Creates and empty CANFrame.

	CANFrame(ID id, Flags flags, DLC dlc, const Payload& payload);
		/// Creates a CANFrame with the given data.
		/// Maximum data length is 8 bytes.

	CANFrame(ID id, Flags flags, DLC dlc, const char* payload);
		/// Creates a CANFrame with the given data.
		/// Maximum data length is 8 bytes.

	CANFrame(const CANFrame& frame);
		/// Creates a CANFrame by copying another one.

	~CANFrame();
		/// Destroys the CANFrame.

	void assign(const CANFrame& frame);
		/// Copies data and flags over from another CANFrame.

	void assign(ID id, Flags flags, DLC dlc, const char* payload);
		/// Changes the frame's data to the given.

	void assign(ID id, Flags flags, DLC dlc, const Payload& payload);
		/// Changes the frame's data to the given.

	CANFrame& operator = (const CANFrame& frame);
		/// Copies data and flags over from another CANFrame.

	void swap(CANFrame& frame);
		/// Swaps the contents of the frame with those of another.

	ID id() const;
		/// Returns the ID of the frame.

	Flags flags() const;
		/// Returns the flags of the frame.

	DLC dlc() const;
		/// Returns the length of the data (Data Length Code).

	const Payload& payload() const;
		/// Returns a pointer to the internal buffer containing the data.

	Payload& payload();
		/// Returns a pointer to the internal buffer containing the data.

	// Serialization support
	void id(ID n);
		/// Sets the ID of the frame.

	void flags(Flags f);
		/// Sets the flags.

	void dlc(DLC len);
		/// Sets the Data Length Code.

	void payload(const Payload& p);
		/// Sets the payload.

private:
	//@ order=1
	ID _id;
	//@ order=2, optional
	Flags _flags;
	//@ order=3
	DLC _dlc;
	//@ order=4
	Payload _payload;
};


//
// inlines
//
inline CANFrame::ID CANFrame::id() const
{
	return _id;
}


inline CANFrame::Flags CANFrame::flags() const
{
	return _flags;
}


inline CANFrame::DLC CANFrame::dlc() const
{
	return _dlc;
}


inline const CANFrame::Payload& CANFrame::payload() const
{
	return _payload;
}


inline CANFrame::Payload& CANFrame::payload()
{
	return _payload;
}


inline void CANFrame::id(ID i)
{
	_id = i;
}


inline void CANFrame::flags(Flags f)
{
	_flags = f;
}


inline void CANFrame::dlc(DLC len)
{
	if (len <= MAX_PAYLOAD_SIZE)
		_dlc = len;
	else
		throw Poco::InvalidArgumentException("CAN payload too large");
}


inline void CANFrame::payload(const CANFrame::Payload& p)
{
	_payload = p;
}


inline void swap(CANFrame& frame1, CANFrame& frame2)
{
	frame1.swap(frame2);
}


} } // namespace IoT::CAN


#endif // IoT_CAN_CANFrame_INCLUDED
