//
// Sensor.cpp
//
// Library: IoT/Devices
// Package: Devices
// Module:  Sensor
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/Sensor.h"
#include "Poco/RemotingNG/Context.h"
#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/ORB.h"


using namespace std::string_literals;


namespace IoT {
namespace Devices {


std::string Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS("Cel");
std::string Sensor::PHYSICAL_UNIT_DEGREES_FAHRENHEIT("[degF]");
std::string Sensor::PHYSICAL_UNIT_KELVIN("K");
std::string Sensor::PHYSICAL_UNIT_METER("m");
std::string Sensor::PHYSICAL_UNIT_KILOGRAM("kg");
std::string Sensor::PHYSICAL_UNIT_SECOND("s");
std::string Sensor::PHYSICAL_UNIT_VOLT("V");
std::string Sensor::PHYSICAL_UNIT_AMPERE("A");
std::string Sensor::PHYSICAL_UNIT_MOL("mol");
std::string Sensor::PHYSICAL_UNIT_CANDELA("cd");
std::string Sensor::PHYSICAL_UNIT_LUX("lx");
std::string Sensor::PHYSICAL_UNIT_MBAR("mbar");


Sensor::Sensor()
{
}


Sensor::~Sensor()
{
}


void Sensor::clearValueChangedFilter(const std::string& subscriberURI)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->removeEventFilter(subscriberURI, "valueChanged"s);
}


void Sensor::setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsGreaterThanFilter<double>(limit));
}


void Sensor::setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsGreaterThanOrEqualToFilter<double>(limit));
}


void Sensor::setValueChangedIsLessThanFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsLessThanFilter<double>(limit));
}


void Sensor::setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsLessThanOrEqualToFilter<double>(limit));
}


void Sensor::setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumDeltaFilter<double>(delta));
}


void Sensor::setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumIntervalFilter<double>(static_cast<Poco::Clock::ClockDiff>(milliseconds)*1000));
}


void Sensor::setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumIntervalOrDeltaFilter<double>(static_cast<Poco::Clock::ClockDiff>(milliseconds)*1000, delta));
}


void Sensor::setValueChangedMinimumIntervalAndDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumIntervalAndDeltaFilter<double>(static_cast<Poco::Clock::ClockDiff>(milliseconds)*1000, delta));
}


void Sensor::setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold)
{
	if (ready())
	{
		setValueChangedFilter(subscriberURI, new Poco::RemotingNG::HysteresisFilter<double>(lowerThreshold, upperThreshold, value()));
	}
	else
	{
		setValueChangedFilter(subscriberURI, new Poco::RemotingNG::HysteresisFilter<double>(lowerThreshold, upperThreshold));
	}
}


void Sensor::setValueChangedFilter(const std::string& subscriberURI, Poco::RemotingNG::EventFilter<double>::Ptr pFilter)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->setEventFilter<double>(subscriberURI, "valueChanged"s, pFilter);
}


} } // namespace IoT::Devices
