//
// CANFDFrame.h
//
// Library: IoT/CAN
// Package: CANFrame
// Module:  CANEndpoint
//
// Definition of the CANFDFrame class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_CANFDFrame_INCLUDED
#define IoT_CAN_CANFDFrame_INCLUDED


#include "IoT/CAN/CAN.h"
#include "Poco/Exception.h"
#include <vector>


namespace IoT {
namespace CAN {


//@ serialize
class CANFDFrame
	/// A CAN-FD frame.
	///
	/// CAN-FD frames have a variable-length payload of up to 64 bytes.
{
public:
	typedef Poco::UInt32 ID;
	typedef Poco::UInt8  Flags;
	typedef Poco::UInt8  Length;
	typedef std::vector<char> Payload;

	enum Flag
	{
		CAN_FLAG_NONE = 0x00, /// No flags set
		CAN_FLAG_IDE  = 0x01, /// CAN Identifier Extension bit (signalling extended frame format)
		CAN_FLAG_RTR  = 0x02, /// CAN Remote Transmission Request bit
		CAN_FLAG_SRR  = 0x04, /// CAN Substitute Remote Request bit (extended frame only, currently unused)
		CAN_FLAG_ERR  = 0x08, /// Error frame indicator
		CAN_FLAG_FD   = 0x80  /// CAN-FD frame indicator (receive only)
	};

	enum
	{
		MAX_PAYLOAD_SIZE = 64
	};

	CANFDFrame();
		/// Creates and empty CANFDFrame.

	CANFDFrame(ID id, Flags flags, const Payload& payload);
		/// Creates a CANFDFrame with the given data.
		/// Maximum data length is 64 bytes.

	CANFDFrame(ID id, Flags flags, Length length, const char* payload);
		/// Creates a CANFDFrame with the given data.
		/// Maximum data length is 64 bytes.

	CANFDFrame(const CANFDFrame& frame);
		/// Creates a CANFDFrame by copying another one.

	~CANFDFrame();
		/// Destroys the CANFDFrame.

	void assign(const CANFDFrame& frame);
		/// Copies data and flags over from another CANFDFrame.

	void assign(ID id, Flags flags, Length length, const char* payload);
		/// Changes the frame's data to the given.

	void assign(ID id, Flags flags, const Payload& payload);
		/// Changes the frame's data to the given.

	CANFDFrame& operator = (const CANFDFrame& frame);
		/// Copies data and flags over from another CANFDFrame.

	void swap(CANFDFrame& frame);
		/// Swaps the contents of the frame with those of another.

	ID id() const;
		/// Returns the ID of the frame.

	Flags flags() const;
		/// Returns the flags of the frame.

	Length length() const;
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

	void payload(const Payload& p);
		/// Sets the payload.

private:
	//@ order=1
	ID _id;
	//@ order=2, optional
	Flags _flags;
	//@ order=3
	Payload _payload;
};


//
// inlines
//
inline CANFDFrame::ID CANFDFrame::id() const
{
	return _id;
}


inline CANFDFrame::Flags CANFDFrame::flags() const
{
	return _flags;
}


inline CANFDFrame::Length CANFDFrame::length() const
{
	return static_cast<Length>(_payload.size());
}


inline const CANFDFrame::Payload& CANFDFrame::payload() const
{
	return _payload;
}


inline CANFDFrame::Payload& CANFDFrame::payload()
{
	return _payload;
}


inline void CANFDFrame::id(ID i)
{
	_id = i;
}


inline void CANFDFrame::flags(Flags f)
{
	_flags = f;
}


inline void CANFDFrame::payload(const CANFDFrame::Payload& p)
{
	if (p.size() <= MAX_PAYLOAD_SIZE)
		_payload = p;
	else
		throw Poco::InvalidArgumentException("CAN-FD payload too large");
}


inline void swap(CANFDFrame& frame1, CANFDFrame& frame2)
{
	frame1.swap(frame2);
}


} } // namespace IoT::CAN


#endif // IoT_CAN_CANFDFrame_INCLUDED
