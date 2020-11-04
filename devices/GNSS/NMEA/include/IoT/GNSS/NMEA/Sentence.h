//
// Sentence.h
//
// Library: IoT/GNSS/NMEA
// Package: Decoder
// Module:  Sentence
//
// Definition of the NMEA Sentence class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef NMEA_Sentence_INCLUDED
#define NMEA_Sentence_INCLUDED


#include "IoT/GNSS/NMEA/NMEA.h"
#include <vector>
#include <cstdlib>


namespace IoT {
namespace GNSS {
namespace NMEA {


class NMEA_API Sentence
	/// This class represents an NMEA 0183 sentence consisting
	/// of talker ID, sentence type and a variable number of
	/// comma-separated fields, followed by a checksum.
	///
	/// For a complete description of the NMEA 0183 message
	/// format see the NMEA 0183 document available from
	/// the National Marine Electronics Association.
	///
	/// An informal description of the NMEA 0183 message format
	/// can be found at <http://www.catb.org/gpsd/NMEA.html>.
{
public:
	Sentence();
		/// Creates an empty Sentence, with the talker ID
		/// and type set to "XX" and "XXX", respectively.

	Sentence(const std::string& talkerId, const std::string& sentenceType);
		/// Creates an empty NMEA sentence with the given talker ID and
		/// sentence type. Talker ID must be two characters and
		/// message type must be three characters long.
	
	Sentence(const std::string& talkerIdAndSentenceType);
		/// Creates an empty NMEA sentence using the given
		/// talker ID and sentence type, which must be exactly
		/// five characters long.	
	
	Sentence(const Sentence& other);
		/// Creates a Sentence by copying another one.
		
	Sentence& operator = (const Sentence& other);
		/// Assigns a Sentence to another.
		
	~Sentence();
		/// Destroys the Sentence.
		
	void swap(Sentence& other);
		/// Swaps the contents of the Sentence with another one.
		
	const std::string& talkerId() const;
		/// Returns the two-character talker ID (typically
		/// "GP" for GNSS receivers.
		
	const std::string& type() const;
		/// Returns the three-character message type, e.g.
		/// "AAM" or "RMC".
		
	std::size_t size() const;
		/// Returns the number of fields in the message.
		
	const std::string& field(std::size_t index) const;
		/// Returns the value of the field with the given index.
		
	const std::string& operator [] (std::size_t index) const;
		/// Returns the value of the field with the given index.
		
	void addField(const std::string& field);
		/// Adds a field to the Sentence.
		
	void reset(const std::string& talkerIdAndSentenceType);
		/// Sets the talker ID and sentence type and clears all fields.
	
	void reset();
		/// Sets the talker ID and sentence type to XXXXX and
		/// clears all fields.

private:
	typedef std::vector<std::string> FieldVec;
	
	std::string _talkerId;
	std::string _type;
	FieldVec _fields;	

	static const std::string UNKNOWN_TALKER_AND_TYPE;
};


//
// inlines
//
inline const std::string& Sentence::talkerId() const
{
	return _talkerId;
}


inline const std::string& Sentence::type() const
{
	return _type;
}


inline std::size_t Sentence::size() const
{
	return _fields.size();
}


inline const std::string& Sentence::field(std::size_t index) const
{
	poco_assert (index < _fields.size());
	
	return _fields[index];
}


inline const std::string& Sentence::operator [] (std::size_t index) const
{
	poco_assert (index < _fields.size());
	
	return _fields[index];
}


} } } // namespace IoT::GNSS::NMEA


#endif // NMEA_Sentence_INCLUDED
