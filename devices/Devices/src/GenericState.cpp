//
// GenericState.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GenericState.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Devices {


const std::string GenericState::TYPE("io.macchina.state");


GenericState::GenericState(const std::string& name, const std::string& symbolicName, const StateStringMap& stateStringMap):
	_name(name),
	_symbolicName(symbolicName),
	_stateStringMap(stateStringMap),
	_state(0)
{
	addProperty("displayValue", &GenericState::getDisplayValue);
	addProperty("symbolicName", &GenericState::getSymbolicName);
	addProperty("name", &GenericState::getName);
	addProperty("type", &GenericState::getType);
}


GenericState::~GenericState()
{
}


State::StateType GenericState::state() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _state;
}


Poco::Any GenericState::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	std::string result;
	StateStringMap::const_iterator it = _stateStringMap.find(_state);
	if (it != _stateStringMap.end())
	{
		result = it->second;
	}
	else
	{
		result = Poco::NumberFormatter::format(_state);
	}

	return result;
}


Poco::Any GenericState::getName(const std::string&) const
{
	return _name;
}


Poco::Any GenericState::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any GenericState::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


void GenericState::update(StateType state)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (state != _state)
	{
		_state = state;
		lock.unlock();

		stateChanged(this, state);
	}
}


} } // namespace IoT::Devices
