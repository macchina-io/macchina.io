//
// BlueZGATTClient.cpp
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  BlueZGATTClient
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BlueZGATTClient.h"
#include "Poco/StringTokenizer.h"
#include "Poco/File.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"


using namespace std::string_literals;


namespace IoT {
namespace BtLE {
namespace BlueZ {


BlueZGATTClient::BlueZGATTClient(const std::string helperPath):
	HelperClient(helperPath),
	_state(GATT_STATE_DISCONNECTED),
	_connectMode(GATT_CONNECT_WAIT),
	_securityLevel(GATT_SECURITY_LOW),
	_mtu(0),
	_timeout(DEFAULT_TIMEOUT),
	_logger(Poco::Logger::get("IoT.BtLT.BlueZGATTClient"s))
{
}


BlueZGATTClient::~BlueZGATTClient()
{
	try
	{
		disconnect();
	}
	catch (...)
	{
	}
}


void BlueZGATTClient::connect(const std::string& address, ConnectMode mode)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_DISCONNECTED)
		throw Poco::IllegalStateException("can only connect if current state is disconnected"s);

	_logger.debug("Connecting to peripheral %s..."s, address);

	changeState(GATT_STATE_CONNECTING);
	_connectMode = mode;
	try
	{
		startHelper();
		sendCommand("conn " + address);
		if (mode == GATT_CONNECT_WAIT)
		{
			ParsedResponse::Ptr pResponse = expectResponse("stat"s, _timeout);
			if (decodeValue(pResponse->get("state"s)) == "tryconn"s)
			{
				pResponse = expectResponse("stat"s, _timeout);
			}
			std::string state = decodeValue(pResponse->get("state"s));
			if (state == "disc"s)
			{
				expectResponse("err"s, DISCONNECT_TIMEOUT);
			}
			else if (state != "conn"s)
			{
				_logger.warning("Invalid state after connect: %s"s, state);
			}
		}
	}
	catch (...)
	{
		changeState(GATT_STATE_DISCONNECTED);
		_address.clear();
		throw;
	}
}


void BlueZGATTClient::disconnect()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() == GATT_STATE_CONNECTED)
	{
		_logger.debug("Disconnecting from peripheral %s..."s, _address);

		changeState(GATT_STATE_DISCONNECTING);
		if (helperRunning())
		{
			try
			{
				sendCommand("disc");
				ParsedResponse::Ptr pResponse = expectResponse("stat"s, DISCONNECT_TIMEOUT);
				std::string state = decodeValue(pResponse->get("state"s));
				if (state != "disc"s)
				{
					_logger.warning("invalid state after disconnect: %s"s, state);
				}
			}
			catch (Poco::Exception& exc)
			{
				_logger.log(exc);
			}
		}
		changeState(GATT_STATE_DISCONNECTED);
		_address.clear();

		_logger.debug("Disconnected."s);
	}
	stopHelper();
}


GATTClient::State BlueZGATTClient::state() const
{
	Poco::FastMutex::ScopedLock lock(_stateMutex);

	return _state;
}


std::string BlueZGATTClient::address() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _address;
}


std::vector<GATTClient::Service> BlueZGATTClient::services()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected"s);

	if (_services.empty())
	{
		sendCommand("svcs");
		ParsedResponse::Ptr pResponse = expectResponse("find"s, _timeout);
		ParsedResponse::const_iterator it = pResponse->find("hstart"s);
		ParsedResponse::const_iterator end = pResponse->end();
		Service service;
		while (it != end)
		{
			if (it->first == "hstart"s)
			{
				service.firstHandle = decodeWord(it->second);
			}
			else if (it->first == "hend"s)
			{
				service.lastHandle = decodeWord(it->second);
			}
			else if (it->first == "uuid"s)
			{
				service.uuid = Poco::UUID(decodeValue(it->second));
				ServiceDesc::Ptr pServiceDesc = new ServiceDesc;
				pServiceDesc->service = service;
				_services[service.uuid] = pServiceDesc;
			}
			++it;
		}
	}

	std::vector<GATTClient::Service> result;
	for (ServiceMap::const_iterator it = _services.begin(); it != _services.end(); ++it)
	{
		result.push_back(it->second->service);
	}

	return result;
}


std::vector<GATTClient::Service> BlueZGATTClient::includedServices(const Poco::UUID& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	throw Poco::NotImplementedException("BlueZGATTClient::includedServices"s);
}


std::vector<GATTClient::Characteristic> BlueZGATTClient::characteristics(const Poco::UUID& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected"s);

	ServiceMap::iterator it = _services.find(serviceUUID);
	if (it == _services.end())
		throw Poco::NotFoundException("Service"s, serviceUUID.toString());

	if (it->second->characteristics.empty())
	{
		sendCommand(Poco::format("char %hx %hx"s, it->second->service.firstHandle, it->second->service.lastHandle));
		ParsedResponse::Ptr pResponse = expectResponse("find"s, _timeout);
		ParsedResponse::const_iterator itr = pResponse->find("hnd"s);
		ParsedResponse::const_iterator end = pResponse->end();
		Characteristic chara;
		while (itr != end)
		{
			if (itr->first == "hnd"s)
			{
				chara.handle = decodeWord(itr->second);
				if (!it->second->characteristics.empty())
				{
					it->second->characteristics.back().lastHandle = chara.handle - 1;
				}
			}
			else if (itr->first == "props"s)
			{
				chara.properties = decodeWord(itr->second);
			}
			else if (itr->first == "vhnd"s)
			{
				chara.valueHandle = decodeWord(itr->second);
			}
			else if (itr->first == "uuid"s)
			{
				chara.uuid = Poco::UUID(decodeValue(itr->second));
				it->second->characteristics.push_back(chara);
			}
			++itr;
		}
		if (!it->second->characteristics.empty())
		{
			it->second->characteristics.back().lastHandle = it->second->service.lastHandle;
		}
	}

	return it->second->characteristics;
}


std::vector<GATTClient::Descriptor> BlueZGATTClient::descriptors(const Poco::UUID& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected"s);

	ServiceMap::iterator it = _services.find(serviceUUID);
	if (it == _services.end())
		throw Poco::NotFoundException("Service"s, serviceUUID.toString());

	if (it->second->descriptors.empty())
	{
		sendCommand(Poco::format("desc %hx %hx"s, it->second->service.firstHandle, it->second->service.lastHandle));
		ParsedResponse::Ptr pResponse = expectResponse("desc"s, _timeout);
		ParsedResponse::const_iterator itr = pResponse->find("hnd"s);
		ParsedResponse::const_iterator end = pResponse->end();
		Descriptor desc;
		while (itr != end)
		{
			if (itr->first == "hnd"s)
			{
				desc.handle = decodeWord(itr->second);
			}
			else if (itr->first == "uuid"s)
			{
				desc.uuid = Poco::UUID(decodeValue(itr->second));
				it->second->descriptors.push_back(desc);
			}
			++itr;
		}
	}

	return it->second->descriptors;
}


std::string BlueZGATTClient::read(Handle handle)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected"s);

	sendCommand(Poco::format("rd %hx"s, handle));
	ParsedResponse::Ptr pResponse = expectResponse("rd"s, _timeout);
	return decodeValue(pResponse->get("d"s));
}


void BlueZGATTClient::write(Handle handle, const std::string& value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected"s);

	if (value.empty())
		throw Poco::InvalidArgumentException("cannot write empty value"s);

	std::string cmd(Poco::format("%s %hx "s, withResponse ? "wrr"s : "wr"s, handle));
	for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		Poco::NumberFormatter::appendHex(cmd, static_cast<unsigned char>(*it), 2);
	}
	sendCommand(cmd);
	expectResponse("wr"s, _timeout);
}


void BlueZGATTClient::write(Handle handle, const char* value, std::size_t size, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected"s);

	if (size == 0)
		throw Poco::InvalidArgumentException("cannot write empty value"s);

	std::string cmd(Poco::format("%s %hx "s, withResponse ? "wrr"s : "wr"s, handle));
	while (size-- > 0)
	{
		Poco::NumberFormatter::appendHex(cmd, static_cast<unsigned char>(*value++), 2);
	}
	sendCommand(cmd);
	expectResponse("wr"s, _timeout);
}


void BlueZGATTClient::setSecurityLevel(SecurityLevel level)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	throw Poco::NotImplementedException("BlueZGATTClient::setSecurityLevel"s);
}


GATTClient::SecurityLevel BlueZGATTClient::getSecurityLevel() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _securityLevel;
}


void BlueZGATTClient::setMTU(Poco::UInt8 mtu)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	throw Poco::NotImplementedException("BlueZGATTClient::setMTU"s);
}


Poco::UInt8 BlueZGATTClient::getMTU() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _mtu;
}


void BlueZGATTClient::setTimeout(long timeout)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_timeout = timeout;
}


long BlueZGATTClient::getTimeout() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _timeout;
}


void BlueZGATTClient::changeState(State state)
{
	bool stateChanged = false;
	{
		Poco::FastMutex::ScopedLock lock(_stateMutex);

		stateChanged = (state != _state);
		_state = state;
	}

	if (stateChanged)
	{
		switch (state)
		{
		case GATT_STATE_CONNECTED:
			connected.notifyAsync(this);
			break;
		case GATT_STATE_DISCONNECTED:
			disconnected.notifyAsync(this);
			break;
		case GATT_STATE_CONNECTING:
		case GATT_STATE_DISCONNECTING:
			break;
		}
	}
}


void BlueZGATTClient::processResponse(const std::string& response)
{
	if (!response.empty() && response[0] == '#') return;

	ParsedResponse::Ptr pResponse = new ParsedResponse;
	parseResponse(response, *pResponse);

	bool queueResponse = false;
	if (pResponse->type() == "ind"s)
	{
		std::string data = decodeValue(pResponse->get("d"s));
		Indication ind;
		ind.handle = decodeWord(pResponse->get("hnd"s));
		ind.data.assign(data.begin(), data.end());
		try
		{
			indicationReceived(this, ind);
		}
		catch (...)
		{
		}
	}
	else if (pResponse->type() == "ntfy"s)
	{
		std::string data = decodeValue(pResponse->get("d"s));
		Notification nf;
		nf.handle = decodeWord(pResponse->get("hnd"s));
		nf.data.assign(data.begin(), data.end());
		try
		{
			notificationReceived(this, nf);
		}
		catch (...)
		{
		}
	}
	else if (pResponse->type() == "stat"s)
	{
		queueResponse = (_connectMode == GATT_CONNECT_WAIT || state() != GATT_STATE_CONNECTING);
		std::string state = decodeValue(pResponse->get("state"s));
		if (state == "tryconn"s)
		{
			changeState(GATT_STATE_CONNECTING);
		}
		else if (state == "conn")
		{
			_mtu = decodeWord(pResponse->get("mtu"s));
			std::string sec = decodeValue(pResponse->get("sec"s));
			if (sec == "low"s)
				_securityLevel = GATT_SECURITY_LOW;
			else if (sec == "medium"s)
				_securityLevel = GATT_SECURITY_MEDIUM;
			else if (sec == "high"s)
				_securityLevel = GATT_SECURITY_HIGH;
			else
				_logger.warning("received invalid security level: %s"s, sec);
			_address = decodeValue(pResponse->get("dst"s));
			changeState(GATT_STATE_CONNECTED);
			_logger.information("Connected to %s"s, _address);
		}
		else if (state == "disc"s)
		{
			changeState(GATT_STATE_DISCONNECTED);
		}
	}
	else if (pResponse->type() == "err"s)
	{
		std::string code = decodeValue(pResponse->get("code"s));
		std::string msg = decodeValue(pResponse->get("emsg"s, std::string()));
		if (!msg.empty())
		{
			code += ": ";
			code += msg;
		}
		error(code);
		queueResponse = _state != GATT_STATE_DISCONNECTED;
	}
	else if (pResponse->type() == "scan"s)
	{
		// ignore
	}
	else
	{
		queueResponse = true;
	}
	if (queueResponse)
	{
		enqueueResponse(pResponse);
	}
}


} } } // namespace IoT::BtLE::BlueZ
