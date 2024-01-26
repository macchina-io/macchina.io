//
// SettingsServiceRemoteObject.cpp
//
// Library: IoT/Settings
// Package: Generated
// Module:  SettingsServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Settings/SettingsServiceRemoteObject.h"


namespace IoT {
namespace Settings {


SettingsServiceRemoteObject::SettingsServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject):
	IoT::Settings::ISettingsService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


SettingsServiceRemoteObject::~SettingsServiceRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace Settings
} // namespace IoT

