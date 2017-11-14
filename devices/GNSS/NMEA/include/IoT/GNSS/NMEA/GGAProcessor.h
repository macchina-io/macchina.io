//
// GGAProcessor.h
//
// Library: IoT/GNSS/NMEA
// Package: Sentences
// Module:  GGAProcessor
//
// Definition of the GGAProcessor class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef NMEA_GGAProcessor_INCLUDED
#define NMEA_GGAProcessor_INCLUDED


#include "IoT/GNSS/NMEA/NMEA.h"
#include "IoT/GNSS/NMEA/Sentence.h"
#include "Poco/Geo/LatLon.h"
#include "Poco/Geo/Angle.h"
#include "Poco/Timestamp.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace GNSS {
namespace NMEA {


class NMEA_API GGAProcessor
	/// This class processes NMEA-0183 GGA sentences.
{
public:
	enum FixQuality
	{
		FIX_NOT_AVAILABLE = 0,
		FIX_GNSS = 1,
		FIX_DGNSS = 2,
		FIX_PPS = 3,
		FIX_RTK = 4,
		FIX_FLOAT_RTK = 5,
		FIX_ESTIMATED = 6,
		FIX_MANUAL_INPUT = 7,
		FIX_SIMULATION = 8,
		FIX_UNKNOWN = 99
	};
	
	struct GGA
	{
		Poco::Timestamp   utc;
		Poco::Geo::LatLon position;
		FixQuality        quality;
		int               satellitesInView;
		double            hdop;
		double            altitude;
	};
	
	Poco::BasicEvent<const GGA> ggaReceived;
		/// Fired when a valid GGA sentence has been received.
	
	GGAProcessor();
		/// Creates the GGAProcessor.
		
	~GGAProcessor();
		/// Destroys the GGAProcessor.
	
	void processSentence(const Sentence& sentence);
		/// Handles a NMEA Sentence if it's an GGA Sentence.
};


} } } // namespace IoT::GNSS::NMEA


#endif // NMEA_GGAProcessor_INCLUDED
