//
// ScalarDatapoint.cpp
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  ScalarDatapoint
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ScalarDatapoint.h"
#include "Poco/RemotingNG/Context.h"
#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/ORB.h"


using namespace std::string_literals;


namespace IoT {
namespace Devices {


std::string ScalarDatapoint::PHYSICAL_UNIT_DEGREES_CELSIUS("Cel");
std::string ScalarDatapoint::PHYSICAL_UNIT_DEGREES_FAHRENHEIT("[degF]");
std::string ScalarDatapoint::PHYSICAL_UNIT_KELVIN("K");
std::string ScalarDatapoint::PHYSICAL_UNIT_METER("m");
std::string ScalarDatapoint::PHYSICAL_UNIT_KILOGRAM("kg");
std::string ScalarDatapoint::PHYSICAL_UNIT_SECOND("s");
std::string ScalarDatapoint::PHYSICAL_UNIT_VOLT("V");
std::string ScalarDatapoint::PHYSICAL_UNIT_AMPERE("A");
std::string ScalarDatapoint::PHYSICAL_UNIT_MOL("mol");
std::string ScalarDatapoint::PHYSICAL_UNIT_CANDELA("cd");
std::string ScalarDatapoint::PHYSICAL_UNIT_LUX("lx");
std::string ScalarDatapoint::PHYSICAL_UNIT_MBAR("mbar");


ScalarDatapoint::ScalarDatapoint()
{
}


ScalarDatapoint::~ScalarDatapoint()
{
}


void ScalarDatapoint::clearValueChangedFilter(const std::string& subscriberURI)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->removeEventFilter(subscriberURI, "valueChanged"s);
}


void ScalarDatapoint::setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsGreaterThanFilter<double>(limit));
}


void ScalarDatapoint::setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsGreaterThanOrEqualToFilter<double>(limit));
}


void ScalarDatapoint::setValueChangedIsLessThanFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsLessThanFilter<double>(limit));
}


void ScalarDatapoint::setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::IsLessThanOrEqualToFilter<double>(limit));
}


void ScalarDatapoint::setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumDeltaFilter<double>(delta));
}


void ScalarDatapoint::setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumIntervalFilter<double>(static_cast<Poco::Clock::ClockDiff>(milliseconds)*1000));
}


void ScalarDatapoint::setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumIntervalOrDeltaFilter<double>(static_cast<Poco::Clock::ClockDiff>(milliseconds)*1000, delta));
}


void ScalarDatapoint::setValueChangedMinimumIntervalAndDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	setValueChangedFilter(subscriberURI, new Poco::RemotingNG::MinimumIntervalAndDeltaFilter<double>(static_cast<Poco::Clock::ClockDiff>(milliseconds)*1000, delta));
}


void ScalarDatapoint::setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold)
{
	const auto v = validValue();
	if (v.isSpecified())
	{
		setValueChangedFilter(subscriberURI, new Poco::RemotingNG::HysteresisFilter<double>(lowerThreshold, upperThreshold, v.value()));
	}
	else
	{
		setValueChangedFilter(subscriberURI, new Poco::RemotingNG::HysteresisFilter<double>(lowerThreshold, upperThreshold));
	}
}


void ScalarDatapoint::setValueChangedFilter(const std::string& subscriberURI, Poco::RemotingNG::EventFilter<double>::Ptr pFilter)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->setEventFilter<double>(subscriberURI, "valueChanged"s, pFilter);
}


} } // namespace IoT::Devices
