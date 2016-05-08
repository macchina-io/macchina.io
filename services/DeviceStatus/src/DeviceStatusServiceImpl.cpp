//
// DeviceStatusServiceImpl.cpp
//
// $Id$
//
// Library: IoT/DeviceStatus
// Package: DeviceStatusServiceImpl
// Module:  DeviceStatusServiceImpl
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DeviceStatusServiceImpl.h"
#include "Poco/Data/Statement.h"
#include "Poco/Data/Transaction.h"
#include "Poco/Timespan.h"
#include "Poco/Path.h"


using namespace Poco::Data::Keywords;


namespace IoT {
namespace DeviceStatus {


DeviceStatusServiceImpl::DeviceStatusServiceImpl(Poco::OSP::BundleContext::Ptr pContext, int maxAge):
	_pContext(pContext),
	_maxAge(maxAge),
	_logger(Poco::Logger::get("IoT.DeviceStatus"))
{
	Poco::Path path(pContext->persistentDirectory());
	path.makeDirectory();
	path.setFileName("devicestatus.sqlite");
	_pSession = new Poco::Data::Session("SQLite", path.toString());
	
	(*_pSession) << 
		"CREATE TABLE IF NOT EXISTS messages ("
		"    id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"    messageClass VARCHAR(64),"
		"    status INTEGER,"
		"    text VARCHAR(1024),"
		"    timestamp DATETIME,"
		"    acknowledged BOOLEAN"
		")", now;
		
	cleanup(true);
}

	
DeviceStatusServiceImpl::~DeviceStatusServiceImpl()
{
}


DeviceStatus DeviceStatusServiceImpl::status() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	int status(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", into(status), now;
	
	return static_cast<DeviceStatus>(status);
}


DeviceStatusChange DeviceStatusServiceImpl::postStatus(const StatusUpdate& statusUpdate)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	StatusMessage message;
	message.messageClass = statusUpdate.messageClass;
	message.status       = statusUpdate.status;
	message.text         = statusUpdate.text;
	message.acknowledged = false;
	
	Poco::Data::Transaction xa(*_pSession, &_logger);

	int previousStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(previousStatus), 
		now;
		
	if (!message.messageClass.empty())
	{
		(*_pSession) << "DELETE FROM messages WHERE messageClass = ?", use(message.messageClass), now;
	}
	
	(*_pSession) << "INSERT INTO messages VALUES (NULL, ?, ?, ?, ?, ?)",
		use(message.messageClass), 
		use(message.status), 
		use(message.text), 
		use(message.timestamp),
		use(message.acknowledged),
		now;

	int currentStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(id), MAX(status) FROM messages WHERE NOT acknowledged", 
		into(message.id),
		into(currentStatus), 
		now;
		
	cleanup();
	
	xa.commit();
	lock.unlock();
	
	DeviceStatusChange change;
	change.previousStatus = static_cast<DeviceStatus>(previousStatus);
	change.currentStatus = static_cast<DeviceStatus>(currentStatus);
	change.message = message;
	
	statusUpdated(this, change);
	if (currentStatus != previousStatus)
	{
		statusChanged(this, change);
	}
	
	return change;
}


DeviceStatus DeviceStatusServiceImpl::clearStatus(const std::string& id)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	Poco::Data::Transaction xa(*_pSession, &_logger);

	int previousStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(previousStatus), 
		now;

	(*_pSession) << "DELETE FROM messages WHERE messageClass = ?",
		useRef(id),
		now;

	int currentStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(currentStatus), 
		now;
	
	xa.commit();
	lock.unlock();

	if (currentStatus != previousStatus)
	{
		DeviceStatusChange change;
		change.previousStatus = static_cast<DeviceStatus>(previousStatus);
		change.currentStatus = static_cast<DeviceStatus>(currentStatus);
		statusChanged(this, change);
	}
	
	return static_cast<DeviceStatus>(currentStatus);
}


DeviceStatus DeviceStatusServiceImpl::acknowledge(int id)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	Poco::Data::Transaction xa(*_pSession, &_logger);

	int previousStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(previousStatus), 
		now;

	(*_pSession) << "UPDATE messages SET acknowledged = 1 WHERE id = ?",
		use(id),
		now;

	int currentStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(currentStatus), 
		now;
	
	xa.commit();
	lock.unlock();

	if (currentStatus != previousStatus)
	{
		DeviceStatusChange change;
		change.previousStatus = static_cast<DeviceStatus>(previousStatus);
		change.currentStatus = static_cast<DeviceStatus>(currentStatus);
		statusChanged(this, change);
	}

	return static_cast<DeviceStatus>(currentStatus);
}


DeviceStatus DeviceStatusServiceImpl::remove(int id)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	Poco::Data::Transaction xa(*_pSession, &_logger);

	int previousStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(previousStatus), 
		now;

	(*_pSession) << "DELETE FROM messages WHERE id = ?",
		use(id),
		now;

	int currentStatus(DEVICE_STATUS_OK);
	(*_pSession) << "SELECT MAX(status) FROM messages WHERE NOT acknowledged", 
		into(currentStatus), 
		now;
	
	xa.commit();
	lock.unlock();

	if (currentStatus != previousStatus)
	{
		DeviceStatusChange change;
		change.previousStatus = static_cast<DeviceStatus>(previousStatus);
		change.currentStatus = static_cast<DeviceStatus>(currentStatus);
		statusChanged(this, change);
	}

	return static_cast<DeviceStatus>(currentStatus);
}


std::vector<StatusMessage> DeviceStatusServiceImpl::messages(int maxMessages) const
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	StatusMessage message;
	int status;
	Poco::Data::Statement select = ((*_pSession) <<
		"SELECT id, messageClass, status, text, timestamp, acknowledged"
		"  FROM messages"
		"  ORDER BY timestamp DESC, id DESC",
		into(message.id),
		into(message.messageClass),
		into(status),
		into(message.text),
		into(message.timestamp),
		into(message.acknowledged),
		limit(1));
	
	std::vector<StatusMessage> result;
	while (!select.done() && (maxMessages == 0 || result.size() < maxMessages))
	{
		select.execute();
		message.status = static_cast<DeviceStatus>(status);
		result.push_back(message);
	}
	return result;
}


void DeviceStatusServiceImpl::reset()
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	(*_pSession) << "DELETE FROM messages", now;	
}


void DeviceStatusServiceImpl::cleanup(bool force)
{
	if (force || _lastCleanup.isElapsed(_lastCleanup.resolution()*3600))
	{
		Poco::DateTime cutoffDate;
		cutoffDate -= Poco::Timespan(0, _maxAge, 0, 0, 0);
		(*_pSession) << "DELETE FROM messages WHERE acknowledged AND timestamp < ?",
			use(cutoffDate),
			now;
		_lastCleanup.update();
	}
}


} } // namespace IoT::DeviceStatus
