//
// SentenceDecoder.cpp
//
// $Id$
//
// Library: IoT/GNSS/NMEA
// Package: Decoder
// Module:  SentenceDecoder
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/GNSS/NMEA/SentenceDecoder.h"


namespace IoT {
namespace GNSS {
namespace NMEA {


SentenceDecoder::SentenceDecoder():
	_state(ST_INIT),
	_checksum(0),
	_computedChecksum(0)
{
}

	
SentenceDecoder::~SentenceDecoder()
{
}


void SentenceDecoder::reset()
{
	_state            = ST_INIT;
	_checksum         = 0;
	_computedChecksum = 0;
	_talkerType.clear();
	_field.clear();	
	_sentence.reset();
}


void SentenceDecoder::processChar(char ch)
{
	switch (_state)
	{
	case ST_INIT:
		init(ch);
		break;
	case ST_START:
		start(ch);
		break;
	case ST_TALKER_TYPE:
		talkerType(ch);
		break;
	case ST_FIELD:
		field(ch);
		break;
	case ST_CHECKSUM:
		checksum(ch);
		break;
	case ST_INVALID:
		invalid(ch);
		break;
	default:
		poco_bugcheck();
	}
}	


void SentenceDecoder::processBuffer(const char* buffer, std::size_t size)
{
	while (size-- > 0)
	{
		processChar(*buffer++);
	}
}


void SentenceDecoder::init(char ch)
{
	switch (ch)
	{
	case '$':
		_checksum         = 0;
		_computedChecksum = 0;
		_talkerType.clear();
		_field.clear();
		_state = ST_START;
		break;
	case '\r':
	case '\n':
		break;
	default:
		_state = ST_INVALID;
		break;
	}
}


void SentenceDecoder::start(char ch)
{
	updateChecksum(ch);
	_talkerType += ch;
	_state = ST_TALKER_TYPE;
}


void SentenceDecoder::talkerType(char ch)
{
	updateChecksum(ch);
	switch (ch)
	{
	case ',':
		if (_talkerType.size() == 5)
		{
			_sentence.reset(_talkerType);
			_state = ST_FIELD;
		}
		else
		{
			_state = ST_INVALID;
		}
		break;
	case '\r':
	case '\n':
		_state = ST_INVALID;
		break;
	default:
		_talkerType += ch;
		if (_talkerType.size() > 5)
		{
			_state = ST_INVALID;
		}
		break;
	}
}


void SentenceDecoder::field(char ch)
{
	switch (ch)
	{
	case ',':
		updateChecksum(ch);
		_sentence.addField(_field);
		_field.clear();
		break;
	case '*':
		_sentence.addField(_field);
		_field.clear();
		_state = ST_CHECKSUM;
		break;		
	case '\r':
	case '\n':
		_state = ST_INVALID;
		break;
	default:
		updateChecksum(ch);
		_field += ch;
		if (_field.size() > NMEA_MAX_FIELD_SIZE)
		{
			_state = ST_INVALID;
		}
		break;
	}
	if (_sentence.size() > NMEA_MAX_FIELD_COUNT)
	{
		_state = ST_INVALID;
	}
}


void SentenceDecoder::checksum(char ch)
{
	switch (ch)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		_checksum *= 16;
		_checksum += ch - '0';
		break;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		_checksum *= 16;
		_checksum += 10 + ch - 'A';
		break;
	case ',':
		sentenceComplete();
		_state = ST_INVALID; // ignore additional fields
		break;
	case '\r':
	case '\n':
		sentenceComplete();
		_state = ST_INIT;
		break;
	default:
		_state = ST_INVALID;
		break;
	}
}


void SentenceDecoder::invalid(char ch)
{
	switch (ch)
	{
	case '\r':
	case '\n':
		_state = ST_INIT;
		break;
	default:
		break;
	}
}


void SentenceDecoder::sentenceComplete()
{
	if (_checksum == _computedChecksum)
	{
		sentenceReceived(this, _sentence);
	}
}


} } } // namespace IoT::GNSS::NMEA
