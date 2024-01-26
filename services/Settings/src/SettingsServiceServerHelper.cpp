//
// SettingsServiceServerHelper.cpp
//
// Library: IoT/Settings
// Package: Generated
// Module:  SettingsServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Settings/SettingsServiceServerHelper.h"
#include "IoT/Settings/SettingsServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Settings {


namespace
{
	Poco::SingletonHolder<SettingsServiceServerHelper> shSettingsServiceServerHelper;
}


SettingsServiceServerHelper::SettingsServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


SettingsServiceServerHelper::~SettingsServiceServerHelper()
{
}


void SettingsServiceServerHelper::shutdown()
{
	SettingsServiceServerHelper::instance().unregisterSkeleton();
	shSettingsServiceServerHelper.reset();
}


Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> SettingsServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new SettingsServiceRemoteObject(oid, pServiceObject);
}


SettingsServiceServerHelper& SettingsServiceServerHelper::instance()
{
	return *shSettingsServiceServerHelper.get();
}


std::string SettingsServiceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void SettingsServiceServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Settings.SettingsService", new SettingsServiceSkeleton);
}


void SettingsServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void SettingsServiceServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Settings.SettingsService", true);
}


} // namespace Settings
} // namespace IoT

