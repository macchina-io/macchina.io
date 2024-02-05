//
// VectorDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  VectorDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/VectorDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string VectorDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.vector.default");
const std::string VectorDatapointImpl::TYPE("io.macchina.datapoint.vector");


VectorDatapointImpl::VectorDatapointImpl(const std::string& id, const Params& params):
	_id(id),
	_name(params.name),
	_access(params.access),
	_value(params.initialValue.value(IoT::Devices::VectorDatapoint::Vector())),
	_valid(params.initialValue.isSpecified())
{
	addProperty("displayValue"s, &VectorDatapointImpl::getDisplayValue);
	addProperty("deviceIdentifier"s, &VectorDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &VectorDatapointImpl::getSymbolicName);
	addProperty("name"s, &VectorDatapointImpl::getName);
	addProperty("type"s, &VectorDatapointImpl::getType);
	addProperty("updated"s, &VectorDatapointImpl::getUpdated);
	addProperty("access"s, &VectorDatapointImpl::getAccess);
}


VectorDatapointImpl::~VectorDatapointImpl()
{
}


VectorDatapointImpl::Vector VectorDatapointImpl::value() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}



Poco::Optional<VectorDatapointImpl::Vector> VectorDatapointImpl::validValue() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<VectorDatapointImpl::Vector>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


void VectorDatapointImpl::update(const VectorDatapointImpl::Vector& value)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		unsafeUpdate(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void VectorDatapointImpl::forceUpdate(const VectorDatapointImpl::Vector& value)
{
	ScopedLock lock(*this);

	unsafeUpdate(value);
}


void VectorDatapointImpl::invalidate()
{
	ScopedLock lock(*this);

	makeInvalid(_valid);
}


bool VectorDatapointImpl::valid() const
{
	ScopedLock lock(*this);

	return _valid;
}


Poco::Any VectorDatapointImpl::getDisplayValue(const std::string&) const
{	
	if (_access & ACCESS_READ)
	{
		if (_valid)
		{
			std::string formatted;
			for (double v: _value)
			{
				if (!formatted.empty()) formatted += ", ";
				Poco::NumberFormatter::append(formatted, v, 0, 1);
			}
			return formatted;
		}
		else return "-"s;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Any VectorDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any VectorDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any VectorDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any VectorDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any VectorDatapointImpl::getUpdated(const std::string&) const
{
	return _updated;
}


Poco::Any VectorDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


void VectorDatapointImpl::unsafeUpdate(const VectorDatapointImpl::Vector& value)
{
	_updated.update();
	bool changed = _value != value;
	_value = value;
	makeValid(_valid, value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


} } // namespace IoT::Datapoints
