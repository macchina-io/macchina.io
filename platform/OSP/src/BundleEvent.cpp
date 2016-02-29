//
// BundleEvent.cpp
//
// $Id: //poco/1.7/OSP/src/BundleEvent.cpp#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleEvent
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleEvent.h"


namespace Poco {
namespace OSP {


BundleEvent::BundleEvent(Bundle::Ptr pBundle, EventKind what):
	_pBundle(pBundle),
	_what(what)
{
}


BundleEvent::BundleEvent(Bundle* pBundle, EventKind what):
	_pBundle(pBundle, true),
	_what(what)
{
}


BundleEvent::BundleEvent(const BundleEvent& event):
	_pBundle(event._pBundle),
	_what(event._what)
{
}


BundleEvent::~BundleEvent()
{
}


BundleEvent& BundleEvent::operator = (const BundleEvent& event)
{
	if (this != &event)
	{
		_pBundle = event._pBundle;
		_what    = event._what;
	}
	return *this;
}


} } // namespace Poco::OSP
