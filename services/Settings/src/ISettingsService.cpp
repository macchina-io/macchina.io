//
// ISettingsService.cpp
//
// Library: IoT/Settings
// Package: Generated
// Module:  ISettingsService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Settings/ISettingsService.h"


namespace IoT {
namespace Settings {


ISettingsService::ISettingsService():
	Poco::OSP::Service()

{
}


ISettingsService::~ISettingsService()
{
}


bool ISettingsService::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Settings::ISettingsService).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& ISettingsService::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Settings.SettingsService");
	return REMOTING__TYPE_ID;
}


const std::type_info& ISettingsService::type() const
{
	return typeid(ISettingsService);
}


} // namespace Settings
} // namespace IoT

