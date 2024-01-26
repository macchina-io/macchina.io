//
// CompositeImpl.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  CompositeImpl
//
// Definition of the CompositeImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CompositeImpl_INCLUDED
#define IoT_Devices_CompositeImpl_INCLUDED


#include "IoT/Devices/Composite.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceListener.h"
#include "Poco/Mutex.h"
#include <vector>


namespace IoT {
namespace Devices {


class IoTDevices_API CompositeImpl: public DeviceImpl<Composite, CompositeImpl>
	/// Default implementation of a Composite device.
	///
	/// This class listens to the service registry and
	/// maintains its list of fragments.
	///
	/// For a Device to be added as a fragment to a CompositeImpl,
	/// the device's service properties must include a property
	/// named "io.macchina.composite" with the value having the
	/// registered service name of the containing Composite.
{
public:
	CompositeImpl(const std::string& serviceName, const std::string& compositeName, Poco::OSP::ServiceRegistry& registry);
		/// Creates the CompositeImpl, using the given ServiceRegistry.

	~CompositeImpl();
		/// Destroys the CompositeImpl.

	CompositeImpl() = delete;

	// Composite
	std::vector<std::string> fragments() const;
	Poco::Optional<std::string> fragmentByName(const std::string& name) const;

	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void onServiceRegistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef);
	void onServiceUnregistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef);
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getCustomData(const std::string&) const;
	void setCustomData(const std::string& name, const Poco::Any& value);

private:
	Poco::Any _name;
	Poco::OSP::ServiceListener::Ptr _pListener;
	std::vector<Poco::OSP::ServiceRef::Ptr> _fragments;
	Poco::Any _customData;
	mutable Poco::FastMutex _mutex;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_CompositeImpl_INCLUDED
