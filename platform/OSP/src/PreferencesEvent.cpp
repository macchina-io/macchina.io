//
// PreferencesEvent.cpp
//
// Library: OSP
// Package: PreferencesService
// Module:  PreferencesEvent
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/PreferencesEvent.h"
#include <algorithm>


namespace Poco {
namespace OSP {


PreferencesEvent::PreferencesEvent(const std::string& name, const std::string& oldValue, const std::string& newValue):
	_name(name),
	_oldValue(oldValue),
	_newValue(newValue)
{
}


PreferencesEvent::PreferencesEvent(const PreferencesEvent& event):
	_name(event._name),
	_oldValue(event._oldValue),
	_newValue(event._newValue)
{
}


PreferencesEvent::~PreferencesEvent()
{
}


PreferencesEvent& PreferencesEvent::operator = (const PreferencesEvent& event)
{
	PreferencesEvent tmp(event);
	swap(tmp);
	return *this;
}


void PreferencesEvent::swap(PreferencesEvent& event)
{
	using std::swap;
	swap(_name, event._name);
	swap(_oldValue, event._oldValue);
	swap(_newValue, event._newValue);
}


} } // namespace Poco::OSP
