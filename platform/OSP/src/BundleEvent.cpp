//
// BundleEvent.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleEvent
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleEvent.h"


namespace Poco {
namespace OSP {


BundleEvent::BundleEvent(Bundle::Ptr pBundle, EventKind what):
	_pBundle(pBundle),
	_what(what),
	_pException(0)
{
}


BundleEvent::BundleEvent(Bundle* pBundle, EventKind what):
	_pBundle(pBundle, true),
	_what(what),
	_pException(0)
{
}


BundleEvent::BundleEvent(Bundle* pBundle, const Poco::Exception& exception):
	_pBundle(pBundle, true),
	_what(EV_BUNDLE_FAILED),
	_pException(exception.clone())
{
}


BundleEvent::BundleEvent(const BundleEvent& event):
	_pBundle(event._pBundle),
	_what(event._what),
	_pException(event._pException)
{
}


BundleEvent::~BundleEvent()
{
	delete _pException;
}


BundleEvent& BundleEvent::operator = (const BundleEvent& event)
{
	if (this != &event)
	{
		_pBundle    = event._pBundle;
		_what       = event._what;
		_pException = event._pException;
	}
	return *this;
}


} } // namespace Poco::OSP
