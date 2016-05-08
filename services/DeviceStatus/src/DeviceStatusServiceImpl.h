//
// DeviceStatusServiceImpl.h
//
// $Id$
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
#include "Poco/Clock.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceImpl: public DeviceStatusService
	/// Default implementation of the DeviceStatusService.
{
public:
	DeviceStatusServiceImpl(Poco::OSP::BundleContext::Ptr pContext, int maxAge);
		/// Creates the DeviceStatusServiceImpl.
		
	~DeviceStatusServiceImpl();
		/// Destroys the DeviceStatusService.
	
	// DeviceStatusService
	DeviceStatus status() const;
	DeviceStatusChange postStatus(const StatusUpdate& statusUpdate);
	DeviceStatus clearStatus(const std::string& id);
	DeviceStatus acknowledge(int id);
	DeviceStatus remove(int id);
	std::vector<StatusMessage> messages(int maxMessages) const;
	void reset();

protected:
	void cleanup(bool force = false);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	int _maxAge;
	Poco::Clock _lastCleanup;
	mutable Poco::SharedPtr<Poco::Data::Session> _pSession;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


} } // namespace IoT::DeviceStatus


#endif // IoT_DeviceStatus_DeviceStatusServiceImpl_INCLUDED
