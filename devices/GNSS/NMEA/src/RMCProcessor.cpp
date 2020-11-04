//
// RMCProcessor.cpp
//
// Library: IoT/GNSS/NMEA
// Package: Sentences
// Module:  RMCProcessor
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/GNSS/NMEA/RMCProcessor.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTime.h"
#include "Poco/NumberParser.h"
#include <cmath>


namespace IoT {
namespace GNSS {
namespace NMEA {


RMCProcessor::RMCProcessor()
{
}

	
RMCProcessor::~RMCProcessor()
{
}


void RMCProcessor::processSentence(const Sentence& sentence)
{
	if (sentence.type() == "RMC" && sentence.size() > 11 && sentence[1] == "A")
	{
		bool valid = true;
		RMC rmc;
		
		try
		{
			if (!sentence[0].empty() && !sentence[8].empty())
			{
				std::string dateTimeStr = sentence[0];
				dateTimeStr += " ";
				dateTimeStr += sentence[8];
				int tzd;
				Poco::DateTime dt = Poco::DateTimeParser::parse("%H%M%s %d%m%y", dateTimeStr, tzd);
				rmc.timestamp = dt.timestamp();
			}
			else
			{
				rmc.timestamp.update();
			}
		
			if (!sentence[2].empty() && !sentence[4].empty())
			{
				double lat = Poco::NumberParser::parseFloat(sentence[2]);
				double latDeg = std::floor(lat/100);
				double latMin = lat - 100*latDeg;
				latDeg += latMin/60;
				if (sentence[3] == "S") latDeg = -latDeg;
				double lon = Poco::NumberParser::parseFloat(sentence[4]);
				double lonDeg = std::floor(lon/100);
				double lonMin = lon - 100*lonDeg;
				lonDeg += lonMin/60;
				if (sentence[5] == "W") lonDeg = -lonDeg;
				rmc.position.assign(Poco::Geo::Angle::fromDegreesLatitude(latDeg), Poco::Geo::Angle::fromDegreesLongitude(lonDeg));
			}
			else
			{
				valid = false;
			}
		
			if (!sentence[6].empty())
			{
				rmc.speed = Poco::NumberParser::parseFloat(sentence[6]);
			}
			else
			{
				rmc.speed = -1.0;
			}
		
			if (!sentence[7].empty())
			{
				double heading = Poco::NumberParser::parseFloat(sentence[7]);
				rmc.heading = Poco::Geo::Angle::fromDegrees(heading);
			}
			else
			{
				rmc.heading = Poco::Geo::Angle::ZERO;
			}
		
			if (!sentence[9].empty())
			{
				double magVar = Poco::NumberParser::parseFloat(sentence[9]);
				if (sentence[10] == "E") magVar = -magVar;
				rmc.magneticVariation = Poco::Geo::Angle::fromDegrees(magVar);
			}
			else
			{
				rmc.magneticVariation = Poco::Geo::Angle::ZERO;
			}
		}
		catch (Poco::Exception&)
		{
			valid = false;
		}
				
		if (valid)
		{
			rmcReceived(this, rmc);
		}
	}
}


} } } // namespace IoT::GNSS::NMEA
