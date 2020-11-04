//
// Sentence.cpp
//
// Library: IoT/GNSS/NMEA
// Package: Decoder
// Module:  Sentence
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/GNSS/NMEA/Sentence.h"
#include <algorithm>


namespace IoT {
namespace GNSS {
namespace NMEA {


const std::string Sentence::UNKNOWN_TALKER_AND_TYPE("XXXXX");


Sentence::Sentence()
{
	reset();
}


Sentence::Sentence(const std::string& talkerId, const std::string& sentenceType):
	_talkerId(talkerId),
	_type(sentenceType)
{
	poco_assert (talkerId.size() == 2);
	poco_assert (sentenceType.size() == 3);
}


Sentence::Sentence(const std::string& talkerIdAndSentenceType)
{
	reset(talkerIdAndSentenceType);
}


Sentence::Sentence(const Sentence& other):
	_talkerId(other._talkerId),
	_type(other._type),
	_fields(other._fields)
{
}


Sentence::~Sentence()
{
}

	
Sentence& Sentence::operator = (const Sentence& other)
{
	Sentence tmp(other);
	swap(tmp);
	return *this;
}

	
void Sentence::swap(Sentence& other)
{
	std::swap(_talkerId, other._talkerId);
	std::swap(_type, other._type);
	std::swap(_fields, other._fields);
}

		
void Sentence::addField(const std::string& field)
{
	_fields.push_back(field);
}


void Sentence::reset(const std::string& talkerIdAndSentenceType)
{
	poco_assert (talkerIdAndSentenceType.size() == 5);
	_talkerId.assign(talkerIdAndSentenceType, 0, 2);
	_type.assign(talkerIdAndSentenceType, 2, 3);
	_fields.clear();
}


void Sentence::reset()
{
	reset(UNKNOWN_TALKER_AND_TYPE);
}


} } } // namespace IoT::GNSS::NMEA
