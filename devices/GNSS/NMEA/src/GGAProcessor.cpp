//
// GGAProcessor.cpp
//
// Library: IoT/GNSS/NMEA
// Package: Sentences
// Module:  GGAProcessor
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/GNSS/NMEA/GGAProcessor.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTime.h"
#include "Poco/NumberParser.h"
#include <cmath>


namespace IoT {
namespace GNSS {
namespace NMEA {


GGAProcessor::GGAProcessor()
{
}

	
GGAProcessor::~GGAProcessor()
{
}


void GGAProcessor::processSentence(const Sentence& sentence)
{
	if (sentence.type() == "GGA" && sentence.size() > 9)
	{
		bool valid = true;
		GGA gga;
		
		try
		{
			if (!sentence[0].empty())
			{
				std::string timeStr = sentence[0];
				int tzd;
				Poco::DateTime dt = Poco::DateTimeParser::parse("%H%M%s", timeStr, tzd);
				Poco::DateTime now;
				gga.utc = Poco::DateTime(now.year(), now.month(), now.day(), dt.hour(), dt.minute(), dt.second()).timestamp();
			}
			else
			{
				gga.utc.update();
			}
		
			if (!sentence[1].empty() && !sentence[3].empty())
			{
				double lat = Poco::NumberParser::parseFloat(sentence[1]);
				double latDeg = std::floor(lat/100);
				double latMin = lat - 100*latDeg;
				latDeg += latMin/60;
				if (sentence[2] == "S") latDeg = -latDeg;
				double lon = Poco::NumberParser::parseFloat(sentence[3]);
				double lonDeg = std::floor(lon/100);
				double lonMin = lon - 100*lonDeg;
				lonDeg += lonMin/60;
				if (sentence[4] == "W") lonDeg = -lonDeg;
				gga.position.assign(Poco::Geo::Angle::fromDegreesLatitude(latDeg), Poco::Geo::Angle::fromDegreesLongitude(lonDeg));
			}
			else
			{
				valid = false;
			}
		
			if (!sentence[5].empty())
			{
				gga.quality = static_cast<FixQuality>(Poco::NumberParser::parseFloat(sentence[5]));
			}
			else
			{
				gga.quality = FIX_UNKNOWN;
			}
		
			if (!sentence[6].empty())
			{
				gga.satellitesInView = Poco::NumberParser::parseFloat(sentence[6]);
			}
			else
			{
				gga.satellitesInView = 0;
			}
		
			if (!sentence[7].empty())
			{
				gga.hdop = Poco::NumberParser::parseFloat(sentence[7]);
			}
			else
			{
				gga.hdop = -9999;
			}

			if (!sentence[8].empty())
			{
				gga.altitude = Poco::NumberParser::parseFloat(sentence[8]);
			}
			else
			{
				gga.altitude = -9999;
			}
		}
		catch (Poco::Exception&)
		{
			valid = false;
		}
				
		if (valid)
		{
			ggaReceived(this, gga);
		}
	}
}


} } } // namespace IoT::GNSS::NMEA
