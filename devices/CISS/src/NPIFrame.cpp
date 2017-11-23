//
// NPIFrame.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "NPIFrame.h"
#include <algorithm>


namespace IoT {
namespace CISS {


NPIFrame::NPIFrame()
{
	init(0, 0);
}


NPIFrame::NPIFrame(const char* data, std::size_t length)
{
	init(data, length);
}


NPIFrame::NPIFrame(const NPIFrame& other):
	_size(other._size)
{
	std::memcpy(_frame, other._frame, other._size);
}


NPIFrame::~NPIFrame()
{
}


void NPIFrame::init(const char* data, std::size_t length)
{
	poco_assert (length <= CISS_MAX_DATA_LENGTH);

	_size = length + 3;
	_frame[0] = CISS_FRAME_START_DELIM;
	_frame[1] = static_cast<char>(length);
	char checksum = _frame[1];
	for (std::size_t i = 0; i < length; i++)
	{
		_frame[i + 2] = data[i];
		checksum ^= data[i];
	}
	_frame[_size - 1] = checksum;
}


NPIFrame& NPIFrame::operator = (const NPIFrame& other)
{
	NPIFrame temp(other);
	swap(temp);
	return *this;
}


void NPIFrame::swap(NPIFrame& other)
{
	std::swap(_size, other._size);
	std::size_t n = std::max(_size, other._size);
	for (std::size_t i = 0; i < n; i++)
	{
		std::swap(_frame[i], other._frame[i]);
	}
}


NPIFrame::ReadStatus NPIFrame::read(NPIFrame& frame, const char* buffer, std::size_t size)
{
	std::size_t i = 0;
	while (i < size)
	{
		while (i < size && static_cast<unsigned char>(buffer[i]) != CISS_FRAME_START_DELIM) i++;
		if (i < size)
		{
			if (i + 2 < size) // length byte + checksum
			{
				std::size_t dataSize = static_cast<unsigned char>(buffer[i + 1]);
				if (dataSize <= CISS_MAX_DATA_LENGTH)
				{
					if (i + 2 + dataSize < size) // 2 length bytes + data + checksum
					{

						NPIFrame tempFrame(buffer + i + 2, dataSize);
						if (tempFrame.checksum() == static_cast<unsigned char>(buffer[i + 2 + dataSize]))
						{
							frame.swap(tempFrame);
							return CISS_FRAME_OK;
						}
					}
					else return CISS_FRAME_NOT_ENOUGH_DATA;
				}
				i++;
			}
			else return CISS_FRAME_NOT_ENOUGH_DATA;
		}
	}
	return size == 0 ? CISS_FRAME_NOT_ENOUGH_DATA : CISS_FRAME_NOT_FOUND;
}


} } // namespace IoT::CISS
