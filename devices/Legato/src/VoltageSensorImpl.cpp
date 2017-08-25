//
// VoltageSensorImpl.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "VoltageSensorImpl.h"
#include "Poco/Process.h"
#include "Poco/Pipe.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Legato {


const std::string VoltageSensorImpl::NAME("Legato Power Supply Voltage Sensor");
const std::string VoltageSensorImpl::TYPE("io.macchina.sensor");
const std::string VoltageSensorImpl::SYMBOLIC_NAME("io.macchina.legato.voltage");
const std::string VoltageSensorImpl::PHYSICAL_QUANTITY("voltage");


VoltageSensorImpl::VoltageSensorImpl(const std::string& cmPath):
	_cmPath(cmPath),
	_voltage(0),
	_logger(Poco::Logger::get("IoT.Legato.VoltageSensorImpl"))
{
	addProperty("symbolicName", &VoltageSensorImpl::getSymbolicName);
	addProperty("name", &VoltageSensorImpl::getName);
	addProperty("type", &VoltageSensorImpl::getType);
	addProperty("physicalQuantity", &VoltageSensorImpl::getPhysicalQuantity);
	addProperty("physicalUnit", &VoltageSensorImpl::getPhysicalUnit);
	addProperty("displayValue", &VoltageSensorImpl::getDisplayValue);
}


VoltageSensorImpl::~VoltageSensorImpl()
{
}


double VoltageSensorImpl::value() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (_lastMeasurement.isElapsed(5000000))
	{
		try
		{
			std::vector<std::string> args;
			args.push_back("ips");
			args.push_back("read");
			Poco::Pipe outputPipe;
			Poco::ProcessHandle ph = Poco::Process::launch(_cmPath, args, 0, &outputPipe, &outputPipe);
			Poco::PipeInputStream istr(outputPipe);
			std::string output;
			Poco::StreamCopier::copyToString(istr, output);
			int rc = ph.wait();
			if (rc == 0)
			{
				if (Poco::NumberParser::tryParseFloat(output, _voltage))
				{
					_voltage /= 1000.0;
				}
				else
				{
					_logger.error("Failed to read temperature from %s output: %s", _cmPath, output);
				}
			}
			else
			{
				_logger.error("Failed to execute %s: %d [%s]", _cmPath, rc, output);
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
		_lastMeasurement.update();
	}
	return _voltage;
}


bool VoltageSensorImpl::ready() const
{
	return true;
}


Poco::Any VoltageSensorImpl::getName(const std::string&) const
{
	return NAME;
}


Poco::Any VoltageSensorImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any VoltageSensorImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any VoltageSensorImpl::getPhysicalQuantity(const std::string&) const
{
	return PHYSICAL_QUANTITY;
}


Poco::Any VoltageSensorImpl::getPhysicalUnit(const std::string&) const
{
	return IoT::Devices::Sensor::PHYSICAL_UNIT_VOLT;
}


Poco::Any VoltageSensorImpl::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 3);
}


} } // namespace IoT::Legato
