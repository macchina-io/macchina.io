//
// DeviceStatusServiceImpl.h
//
// Library: IoT/DeviceStatus
// Package: DeviceStatusServiceImpl
// Module:  DeviceStatusServiceImpl
//
// Definition of the DeviceStatusServiceImpl class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusServiceImpl_INCLUDED
#define IoT_DeviceStatus_DeviceStatusServiceImpl_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Data/Session.h"
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveDispatcher.h"
#include "Poco/Clock.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceImpl: public DeviceStatusService, public Poco::ActiveDispatcher
	/// Default implementation of the DeviceStatusService.
{
public:
	DeviceStatusServiceImpl(Poco::OSP::BundleContext::Ptr pContext, int maxAge);
		/// Creates the DeviceStatusServiceImpl.

	~DeviceStatusServiceImpl();
		/// Destroys the DeviceStatusService.

	// DeviceStatusService
	DeviceStatus status() const;
	DeviceStatus statusOfSource(const std::string& source) const;
	DeviceStatusChange postStatus(const StatusUpdate& statusUpdate);
	void postStatusAsync(const StatusUpdate& statusUpdate);
	DeviceStatus clearStatus(const std::string& messageClass);
	DeviceStatus clearStatusOfSource(const std::string& source);
	DeviceStatus acknowledge(Poco::Int64 id);
	DeviceStatus acknowledgeUpTo(Poco::Int64 id);
	DeviceStatus remove(Poco::Int64 id);
	std::vector<StatusMessage> messages(int maxMessages) const;
	void reset();

protected:
	void cleanup(bool force = false);
	void postStatusAsyncImpl(const StatusUpdate& statusUpdate);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	int _maxAge;
	Poco::Clock _lastCleanup;
	mutable Poco::SharedPtr<Poco::Data::Session> _pSession;
	Poco::ActiveMethod<void, StatusUpdate, DeviceStatusServiceImpl, Poco::ActiveStarter<Poco::ActiveDispatcher>> _postStatusAsync;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


} } // namespace IoT::DeviceStatus


#endif // IoT_DeviceStatus_DeviceStatusServiceImpl_INCLUDED
