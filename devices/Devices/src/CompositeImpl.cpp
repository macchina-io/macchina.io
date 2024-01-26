//
// CompositeImpl.cpp
//
// Library: IoT/Devices
// Package: Devices
// Module:  CompositeImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/CompositeImpl.h"
#include "Poco/Format.h"
#include "Poco/Delegate.h"
#include <algorithm>


using namespace std::string_literals;


namespace IoT {
namespace Devices {


const std::string CompositeImpl::SYMBOLIC_NAME("io.macchina.composite");
const std::string CompositeImpl::TYPE("io.macchina.composite");


CompositeImpl::CompositeImpl(const std::string& serviceName, const std::string& compositeName, Poco::OSP::ServiceRegistry& registry):
	_name(compositeName),
	_customData(std::string())
{
	addProperty("symbolicName"s, &CompositeImpl::getSymbolicName);
	addProperty("name"s, &CompositeImpl::getName);
	addProperty("type"s, &CompositeImpl::getType);
	addProperty("customData"s, &CompositeImpl::getCustomData, &CompositeImpl::setCustomData);

	_pListener = registry.createListener(
		Poco::format("io.macchina.composite == \"%s\""s, serviceName),
		Poco::delegate(this, &CompositeImpl::onServiceRegistered),
		Poco::delegate(this, &CompositeImpl::onServiceUnregistered));
}


CompositeImpl::~CompositeImpl()
{
	_pListener.reset();
	_fragments.clear();
}


std::vector<std::string> CompositeImpl::fragments() const
{	
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::vector<std::string> result;
	result.reserve(_fragments.size());
	for (const auto& pRef: _fragments)
	{
		result.push_back(pRef->name());
	}
	return result;
}


Poco::Optional<std::string> CompositeImpl::fragmentByName(const std::string& nodeName) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (const auto& pRef: _fragments)
	{
		if (pRef->properties().get("io.macchina.nodeName"s, ""s) == nodeName)
		{
			return pRef->name();
		}
	}
	return {};
}


void CompositeImpl::onServiceRegistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_fragments.push_back(pServiceRef);
}


void CompositeImpl::onServiceUnregistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_fragments.erase(
		std::remove_if(_fragments.begin(), _fragments.end(), 
			[&pServiceRef](const Poco::OSP::ServiceRef::Ptr& pFragRef) -> bool
			{
				return pFragRef->name() == pServiceRef->name();
			}
		), 
		_fragments.end()
	);
}


Poco::Any CompositeImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any CompositeImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any CompositeImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any CompositeImpl::getCustomData(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _customData;
}


void CompositeImpl::setCustomData(const std::string& name, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_customData = value;
}


} } // namespace IoT::Devices
