//
// SettingsServiceSkeleton.h
//
// Library: IoT/Settings
// Package: Generated
// Module:  SettingsServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Settings_SettingsServiceSkeleton_INCLUDED
#define IoT_Settings_SettingsServiceSkeleton_INCLUDED


#include "IoT/Settings/SettingsServiceRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Settings {


class SettingsServiceSkeleton: public Poco::RemotingNG::Skeleton
	/// The SettingsService provides a service interface to the
	/// configuration system. Specifically it allows to change
	/// configuration parameters and to save changed parameters
	/// in a file.
{
public:
	SettingsServiceSkeleton();
		/// Creates a SettingsServiceSkeleton.

	virtual ~SettingsServiceSkeleton();
		/// Destroys a SettingsServiceSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SettingsServiceSkeleton::remoting__typeId() const
{
	return ISettingsService::remoting__typeId();
}


} // namespace Settings
} // namespace IoT


#endif // IoT_Settings_SettingsServiceSkeleton_INCLUDED

