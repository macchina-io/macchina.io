//
// RMCProcessor.h
//
// Library: IoT/GNSS/NMEA
// Package: Sentences
// Module:  RMCProcessor
//
// Definition of the RMCProcessor class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef NMEA_RMCProcessor_INCLUDED
#define NMEA_RMCProcessor_INCLUDED


#include "IoT/GNSS/NMEA/NMEA.h"
#include "IoT/GNSS/NMEA/Sentence.h"
#include "Poco/Geo/LatLon.h"
#include "Poco/Geo/Angle.h"
#include "Poco/Timestamp.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace GNSS {
namespace NMEA {


class NMEA_API RMCProcessor
	/// This class processes NMEA-0183 RMC sentences.
{
public:
	struct RMC
	{
		Poco::Geo::LatLon position;
		Poco::Geo::Angle  heading;
		double            speed;
		Poco::Geo::Angle  magneticVariation;
		Poco::Timestamp   timestamp;
	};
	
	Poco::BasicEvent<const RMC> rmcReceived;
		/// Fired when a valid RMC sentence has been received.
	
	RMCProcessor();
		/// Creates the RMCProcessor.
		
	~RMCProcessor();
		/// Destroys the RMCProcessor.
	
	void processSentence(const Sentence& sentence);
		/// Handles a NMEA Sentence if it's an RMC Sentence.
};


} } } // namespace IoT::GNSS::NMEA


#endif // NMEA_RMCProcessor_INCLUDED
