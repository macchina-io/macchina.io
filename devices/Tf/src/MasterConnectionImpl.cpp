//
// MasterConnectionImpl.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "MasterConnectionImpl.h"


namespace IoT {
namespace Tf {


MasterConnectionImpl::MasterConnectionImpl()
{
	ipcon_create(&_ipcon);
}

	
MasterConnectionImpl::~MasterConnectionImpl()
{
	disconnect();
	ipcon_destroy(&_ipcon);
}

	
void MasterConnectionImpl::connect(const std::string& host, Poco::UInt16 port)
{
	poco_assert (ipcon_get_connection_state(&_ipcon) == IPCON_CONNECTION_STATE_DISCONNECTED);
	int rc = ipcon_connect(&_ipcon, host.c_str(), port);
	switch (rc)
	{
	case E_OK:
		break;
	
	case E_TIMEOUT:
		throw Poco::TimeoutException();

	case E_HOSTNAME_INVALID:
		throw Poco::IOException("invalid hostname", host);
			
	default:
		throw Poco::IOException("cannot establish connection to master");
	}
	
	while (ipcon_get_connection_state(&_ipcon) == IPCON_CONNECTION_STATE_PENDING)
	{
		Poco::Thread::sleep(100);
	}
	
	ipcon_register_callback(&_ipcon, IPCON_CALLBACK_ENUMERATE, (void*) enumerate, this);
	rc = ipcon_enumerate(&_ipcon);
	if (rc != E_OK)
	{
		throw Poco::IOException();
	}
}


void MasterConnectionImpl::disconnect()
{
	if (ipcon_get_connection_state(&_ipcon) == IPCON_CONNECTION_STATE_CONNECTED)
	{
		ipcon_disconnect(&_ipcon);
	}
}


bool MasterConnectionImpl::connected() const
{
	return ipcon_get_connection_state(const_cast<IPConnection*>(&_ipcon)) == IPCON_CONNECTION_STATE_CONNECTED;
}


void MasterConnectionImpl::enumerate(
	const char *uid, 
	const char *masterUID,
	char position, 
	uint8_t hardwareVersion[3],
	uint8_t firmwareVersion[3], 
	uint16_t deviceType,
	uint8_t enumType,
	void* arg)
{
	MasterConnectionImpl* pThis = reinterpret_cast<MasterConnectionImpl*>(arg);

	DeviceEvent event;
	switch (enumType)
	{
	case IPCON_ENUMERATION_TYPE_AVAILABLE:
		event.state = DEVICE_AVAILABLE;
		break;
		
	case IPCON_ENUMERATION_TYPE_CONNECTED:
		event.state = DEVICE_CONNECTED;
		break;

	case IPCON_ENUMERATION_TYPE_DISCONNECTED:
		event.state = DEVICE_DISCONNECTED;
		break;
	}

	event.hardwareVersion.major    = hardwareVersion[0];
	event.hardwareVersion.minor    = hardwareVersion[1];
	event.hardwareVersion.revision = hardwareVersion[2];
	
	event.firmwareVersion.major    = firmwareVersion[0];
	event.firmwareVersion.minor    = firmwareVersion[1];
	event.firmwareVersion.revision = firmwareVersion[2];
	
	event.uid = uid;
	event.masterUID = masterUID;
	event.position  = position;
	event.type      = deviceType;
	
	pThis->deviceStateChanged(pThis, event);
}


} } // namespace IoT::Tf
