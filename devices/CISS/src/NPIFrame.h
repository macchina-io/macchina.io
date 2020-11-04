//
// NPIFrame.h
//
// Definition of the NPIFrame class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CISS_NPIFrame_INCLUDED
#define IoT_CISS_NPIFrame_INCLUDED


#include "Poco/Poco.h"
#include <string>


namespace IoT {
namespace CISS {


class NPIFrame
	/// This class encapsulates a CISS NPI frame with start delimiter,
	/// length byte, payload and checksum.
{
public:
	enum
	{
		CISS_MAX_FRAME_LENGTH  = 32,
		CISS_MAX_DATA_LENGTH   = CISS_MAX_FRAME_LENGTH - 3,
		CISS_FRAME_START_DELIM = 0xFE
	};

	enum ReadStatus
	{
		CISS_FRAME_OK,
		CISS_FRAME_NOT_ENOUGH_DATA,
		CISS_FRAME_NOT_FOUND
	};

	NPIFrame();
		/// Creates an empty NPIFrame.

	NPIFrame(const char* data, std::size_t length);
		/// Creates a NPIFrame with the given payload.

	NPIFrame(const NPIFrame& other);
		/// Creates a NPIFrame by copying another one.

	~NPIFrame();
		/// Destroys the NPIFrame.

	NPIFrame& operator = (const NPIFrame& other);
		/// Assignment operator.

	void swap(NPIFrame& other);
		/// Swaps the contents of the frame with another one.

	Poco::UInt8 type() const;
		/// Returns the frame type.

	const char* payload() const;
		/// Returns a pointer to the frame payload.

	std::size_t payloadSize() const;
		/// Returns the frame data size.

	const char* frame() const;
		/// Returns a pointer to the raw NPI frame.

	std::size_t frameSize() const;
		/// Returns the raw frame size.

	static ReadStatus read(NPIFrame& frame, const char* buffer, std::size_t size);
		/// Attempts to read a frame from the given buffer.
		///
		/// Returns:
		///   - CISS_FRAME_OK if a valid frame was found.
		///   - CISS_FRAME_NOT_ENOUGH_DATA if the buffer does not contain enough data
		///     to read the entire frame. Retry again with a buffer containing more data.
		///   - CISS_FRAME_NOT_FOUND if no valid frame was found.

protected:
	void init(const char* data, std::size_t length);
	unsigned char checksum() const;

private:
	char _frame[CISS_MAX_FRAME_LENGTH];
	std::size_t _size;
};


//
// inlines
//
inline Poco::UInt8 NPIFrame::type() const
{
	return static_cast<Poco::UInt8>(_frame[2]);
}


inline const char* NPIFrame::payload() const
{
	return &_frame[2];
}


inline std::size_t NPIFrame::payloadSize() const
{
	return _size - 3;
}


inline const char* NPIFrame::frame() const
{
	return &_frame[0];
}


inline std::size_t NPIFrame::frameSize() const
{
	return _size;
}


inline unsigned char NPIFrame::checksum() const
{
	return static_cast<unsigned char>(_frame[_size - 1]);
}


} } // namespace IoT::CISS


#endif // IoT_CISS_NPIFrame_INCLUDED
