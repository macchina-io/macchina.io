//
// SettingsServiceServerHelper.h
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


#ifndef IoT_Settings_SettingsServiceServerHelper_INCLUDED
#define IoT_Settings_SettingsServiceServerHelper_INCLUDED


#include "IoT/Settings/ISettingsService.h"
#include "IoT/Settings/SettingsService.h"
#include "IoT/Settings/SettingsServiceRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Settings {


class SettingsServiceServerHelper
	/// The SettingsService provides a service interface to the
	/// configuration system. Specifically it allows to change
	/// configuration parameters and to save changed parameters
	/// in a file.
{
public:
	using Service = IoT::Settings::SettingsService;

	SettingsServiceServerHelper();
		/// Creates a SettingsServiceServerHelper.

	~SettingsServiceServerHelper();
		/// Destroys the SettingsServiceServerHelper.

	static Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Settings::SettingsService instance.

	static std::string registerObject(Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Settings::SettingsService instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Settings::SettingsService from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static SettingsServiceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> SettingsServiceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return SettingsServiceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string SettingsServiceServerHelper::registerObject(Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return SettingsServiceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string SettingsServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Settings::SettingsServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SettingsServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void SettingsServiceServerHelper::unregisterObject(const std::string& uri)
{
	SettingsServiceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Settings
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Settings, SettingsService)


#endif // IoT_Settings_SettingsServiceServerHelper_INCLUDED

