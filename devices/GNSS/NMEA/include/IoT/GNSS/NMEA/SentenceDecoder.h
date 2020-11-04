//
// SentenceDecoder.h
//
// Library: IoT/GNSS/NMEA
// Package: Decoder
// Module:  SentenceDecoder
//
// Definition of the SentenceDecoder class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef NMEA_SentenceDecoder_INCLUDED
#define NMEA_SentenceDecoder_INCLUDED


#include "IoT/GNSS/NMEA/NMEA.h"
#include "IoT/GNSS/NMEA/Sentence.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace GNSS {
namespace NMEA {


class NMEA_API SentenceDecoder
	/// This class decodes NMEA-0183 wire-format sentences into
	/// Sentence objects for further processing.
	///
	/// For a complete description of the NMEA 0183 message
	/// format see the NMEA 0183 document available from
	/// the National Marine Electronics Association.
	///
	/// An informal description of the NMEA 0183 message format
	/// can be found at <http://www.catb.org/gpsd/NMEA.html>.
{
public:	
	Poco::BasicEvent<const Sentence> sentenceReceived;
		/// Fired when a valid sentence has been received.
	
	SentenceDecoder();
		/// Creates the SentenceDecoder.
		
	~SentenceDecoder();
		/// Destroys the SentenceDecoder.
	
	void reset();
		/// Resets the decoder to initial state.
	
	void processChar(char ch);
		/// Processes the given character.
		
	void processBuffer(const char* buffer, std::size_t size);
		/// Processes all characters in the given buffer.
		
protected:
	enum State
	{
		ST_INIT,           /// initial state, beginning of message, skipping CR/LF
		ST_START,          /// '$' message start delimiter was found
		ST_TALKER_TYPE,    /// reading talker and sentence type
		ST_FIELD,          /// reading fields
		ST_CHECKSUM,       /// reading checksum
		ST_INVALID         /// invalid characters found
	};
	
	enum Limits
	{
		NMEA_MAX_FIELD_COUNT = 32,
		NMEA_MAX_FIELD_SIZE  = 64
	};
	
	void init(char ch);
	void start(char ch);
	void talkerType(char ch);
	void field(char ch);
	void checksum(char ch);
	void invalid(char ch);
	void updateChecksum(char ch);
	void sentenceComplete();
		
private:
	SentenceDecoder(const SentenceDecoder&);
	SentenceDecoder& operator = (const SentenceDecoder&);
	
	State    _state;
	unsigned char _checksum;
	unsigned char _computedChecksum;
	std::string _talkerType;
	std::string _field;
	Sentence _sentence;
};


//
// inlines
//
inline void SentenceDecoder::updateChecksum(char ch)
{
	_computedChecksum ^= static_cast<unsigned char>(ch);
}


} } } // namespace IoT::GNSS::NMEA


#endif // NMEA_SentenceDecoder_INCLUDED
