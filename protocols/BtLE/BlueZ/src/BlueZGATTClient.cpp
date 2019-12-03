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
// SPDX-License-Identifier: Apache-2.0
//


#include "BlueZGATTClient.h"
#include "Poco/StringTokenizer.h"
#include "Poco/File.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"


namespace IoT {
namespace BtLE {
namespace BlueZ {


BlueZGATTClient::BlueZGATTClient(const std::string helperPath):
	_helperPath(helperPath),
	_state(GATT_STATE_DISCONNECTED),
	_connectMode(GATT_CONNECT_WAIT),
	_securityLevel(GATT_SECURITY_LOW),
	_mtu(0),
	_timeout(DEFAULT_TIMEOUT),
	_logger(Poco::Logger::get("IoT.BlueZGATTClient"))
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
		throw Poco::IllegalStateException("can only connect if current state is disconnected");

	_logger.debug("Connecting to peripheral " + address + "...");

	changeState(GATT_STATE_CONNECTING);
	_connectMode = mode;
	try
	{
		startHelper();
		sendCommand("conn " + address);
		if (mode == GATT_CONNECT_WAIT)
		{
			ParsedResponse::Ptr pResponse = expectResponse("stat", _timeout);
			if (decodeValue(pResponse->get("state")) == "tryconn")
			{
				pResponse = expectResponse("stat", _timeout);
			}
			std::string state = decodeValue(pResponse->get("state"));
			if (state == "disc")
			{
				expectResponse("err", DISCONNECT_TIMEOUT);
			}
			else if (state != "conn")
			{
				_logger.warning("Invalid state after connect: " + state);
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
		_logger.debug("Disconnecting from peripheral " + _address + "...");

		changeState(GATT_STATE_DISCONNECTING);
		if (helperRunning())
		{
			try
			{
				sendCommand("disc");
				ParsedResponse::Ptr pResponse = expectResponse("stat", DISCONNECT_TIMEOUT);
				std::string state = decodeValue(pResponse->get("state"));
				if (state != "disc")
				{
					_logger.warning("invalid state after disconnect: " + state);
				}
			}
			catch (Poco::Exception& exc)
			{
				_logger.log(exc);
			}
		}
		changeState(GATT_STATE_DISCONNECTED);
		_address.clear();

		_logger.debug("Disconnected.");
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
		throw Poco::IllegalStateException("not connected");

	if (_services.empty())
	{
		sendCommand("svcs");
		ParsedResponse::Ptr pResponse = expectResponse("find", _timeout);
		ParsedResponse::const_iterator it = pResponse->find("hstart");
		ParsedResponse::const_iterator end = pResponse->end();
		Service service;
		while (it != end)
		{
			if (it->first == "hstart")
			{
				service.firstHandle = decodeWord(it->second);
			}
			else if (it->first == "hend")
			{
				service.lastHandle = decodeWord(it->second);
			}
			else if (it->first == "uuid")
			{
				service.uuid = decodeValue(it->second);
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


std::vector<GATTClient::Service> BlueZGATTClient::includedServices(const std::string& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	throw Poco::NotImplementedException("BlueZGATTClient::includedServices");
}


std::vector<GATTClient::Characteristic> BlueZGATTClient::characteristics(const std::string& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected");

	ServiceMap::iterator it = _services.find(serviceUUID);
	if (it == _services.end())
		throw Poco::NotFoundException("Service", serviceUUID);

	if (it->second->characteristics.empty())
	{
		sendCommand(Poco::format("char %hx %hx", it->second->service.firstHandle, it->second->service.lastHandle));
		ParsedResponse::Ptr pResponse = expectResponse("find", _timeout);
		ParsedResponse::const_iterator itr = pResponse->find("hnd");
		ParsedResponse::const_iterator end = pResponse->end();
		Characteristic chara;
		while (itr != end)
		{
			if (itr->first == "hnd")
			{
				chara.handle = decodeWord(itr->second);
			}
			else if (itr->first == "props")
			{
				chara.properties = decodeWord(itr->second);
			}
			else if (itr->first == "vhnd")
			{
				chara.valueHandle = decodeWord(itr->second);
			}
			else if (itr->first == "uuid")
			{
				chara.uuid = decodeValue(itr->second);
				it->second->characteristics.push_back(chara);
			}
			++itr;
		}
	}

	return it->second->characteristics;
}


std::vector<GATTClient::Descriptor> BlueZGATTClient::descriptors(const std::string& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected");

	ServiceMap::iterator it = _services.find(serviceUUID);
	if (it == _services.end())
		throw Poco::NotFoundException("Service", serviceUUID);

	if (it->second->descriptors.empty())
	{
		sendCommand(Poco::format("desc %hx %hx", it->second->service.firstHandle, it->second->service.lastHandle));
		ParsedResponse::Ptr pResponse = expectResponse("desc", _timeout);
		ParsedResponse::const_iterator itr = pResponse->find("hnd");
		ParsedResponse::const_iterator end = pResponse->end();
		Descriptor desc;
		while (itr != end)
		{
			if (itr->first == "hnd")
			{
				desc.handle = decodeWord(itr->second);
			}
			else if (itr->first == "uuid")
			{
				desc.uuid = decodeValue(itr->second);
				it->second->descriptors.push_back(desc);
			}
			++itr;
		}
	}

	return it->second->descriptors;
}


std::string BlueZGATTClient::read(Poco::UInt16 handle)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected");

	sendCommand(Poco::format("rd %hx", handle));
	ParsedResponse::Ptr pResponse = expectResponse("rd", _timeout);
	return decodeValue(pResponse->get("d"));
}


void BlueZGATTClient::write(Poco::UInt16 handle, const std::string& value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (state() != GATT_STATE_CONNECTED)
		throw Poco::IllegalStateException("not connected");

	if (value.empty())
		throw Poco::InvalidArgumentException("cannot write empty value");

	std::string cmd(Poco::format("%s %hx ", std::string(withResponse ? "wrr" : "wr"), handle));
	for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		Poco::NumberFormatter::appendHex(cmd, static_cast<unsigned char>(*it), 2);
	}
	sendCommand(cmd);
	if (withResponse)
	{
		expectResponse("wr", _timeout);
	}
}


void BlueZGATTClient::setSecurityLevel(SecurityLevel level)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	throw Poco::NotImplementedException("BlueZGATTClient::setSecurityLevel");
}


GATTClient::SecurityLevel BlueZGATTClient::getSecurityLevel() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _securityLevel;
}


void BlueZGATTClient::setMTU(Poco::UInt8 mtu)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	throw Poco::NotImplementedException("BlueZGATTClient::setMTU");
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


void BlueZGATTClient::startHelper()
{
	if (!_pHelperInfo)
	{
		_logger.debug(Poco::format("Starting helper: %s...", _helperPath));
		Poco::File helperExec(_helperPath);
		if (!helperExec.exists())
			throw Poco::FileNotFoundException("helper executable not found", _helperPath);
		if (!helperExec.canExecute())
			throw Poco::FileException("helper executable does not have execute permission", _helperPath);

		Poco::Pipe inputPipe;
		Poco::Pipe outputPipe;
		Poco::Process::Args args;
		Poco::ProcessHandle ph = Poco::Process::launch(_helperPath, args, &inputPipe, &outputPipe, 0);
		_pHelperInfo = new HelperInfo(ph, inputPipe, outputPipe);
		_helperThread.start(*this);
		_logger.debug("Helper started.");
	}
}


void BlueZGATTClient::stopHelper()
{
	if (_pHelperInfo)
	{
		_logger.debug("Stopping helper...");
		if (helperRunning())
		{
			try
			{
				sendCommand("quit");
			}
			catch (Poco::Exception&)
			{
			}
		}
		try
		{
			_helperThread.join(10000);
		}
		catch (Poco::TimeoutException&)
		{
			_logger.debug("Helper failed to quit in time, killing...");
			Poco::Process::kill(_pHelperInfo->processHandle);
			try
			{
				_helperThread.join();
			}
			catch (Poco::Exception& exc)
			{
				_logger.debug("Failed to join helper thread: %s", exc.displayText());
			}
		}
		_pHelperInfo = 0;
		_logger.debug("Helper stopped.");
	}
}


bool BlueZGATTClient::helperRunning()
{
	return _pHelperInfo && _pHelperInfo->outputStream.good();
}


void BlueZGATTClient::run()
{
	std::string response;
	while (_pHelperInfo->inputStream.good())
	{
		std::getline(_pHelperInfo->inputStream, response);
		if (!response.empty())
		{
			try
			{
				processResponse(response);
			}
			catch (Poco::Exception& exc)
			{
				_logger.log(exc);
			}
		}
	}
	_logger.debug("Helper process terminated");
	try
	{
		 _pHelperInfo->processHandle.wait();
	}
	catch (Poco::Exception& exc)
	{
		_logger.debug("Failed to wait for helper process: %s", exc.displayText());
	}
}


void BlueZGATTClient::sendCommand(const std::string& command)
{
	if (helperRunning())
	{
		_logger.debug(Poco::format("[%s] Sending command: %s", _address, command));

		if (!_responseQueue.empty())
		{
			_logger.debug("Response queue not empty");
			_responseQueue.clear();
		}

		_pHelperInfo->outputStream << command << std::endl;
		if (!_pHelperInfo->outputStream.good())
		{
			_pHelperInfo = 0;
			throw Poco::IOException("helper process no longer running");
		}
	}
	else throw Poco::IllegalStateException("helper process not running");
}


void BlueZGATTClient::processResponse(const std::string& response)
{
	if (!response.empty() && response[0] == '#') return;

	ParsedResponse::Ptr pResponse = new ParsedResponse;
	parseResponse(response, *pResponse);

	bool queueResponse = false;
	if (pResponse->type() == "ind")
	{
		Indication ind;
		ind.handle = decodeWord(pResponse->get("hnd"));
		ind.data = decodeValue(pResponse->get("d"));
		try
		{
			indicationReceived(this, ind);
		}
		catch (...)
		{
		}
	}
	else if (pResponse->type() == "ntfy")
	{
		Notification nf;
		nf.handle = decodeWord(pResponse->get("hnd"));
		nf.data = decodeValue(pResponse->get("d"));
		try
		{
			notificationReceived(this, nf);
		}
		catch (...)
		{
		}
	}
	else if (pResponse->type() == "stat")
	{
		queueResponse = (_connectMode == GATT_CONNECT_WAIT || state() != GATT_STATE_CONNECTING);
		std::string state = decodeValue(pResponse->get("state"));
		if (state == "tryconn")
		{
			changeState(GATT_STATE_CONNECTING);
		}
		else if (state == "conn")
		{
			_mtu = decodeWord(pResponse->get("mtu"));
			std::string sec = decodeValue(pResponse->get("sec"));
			if (sec == "low")
				_securityLevel = GATT_SECURITY_LOW;
			else if (sec == "medium")
				_securityLevel = GATT_SECURITY_MEDIUM;
			else if (sec == "high")
				_securityLevel = GATT_SECURITY_HIGH;
			else
				_logger.warning("received invalid security level: " + sec);
			_address = decodeValue(pResponse->get("dst"));
			changeState(GATT_STATE_CONNECTED);
			_logger.information("Connected to " + _address);
		}
		else if (state == "disc")
		{
			changeState(GATT_STATE_DISCONNECTED);
		}
	}
	else if (pResponse->type() == "err")
	{
		std::string code = decodeValue(pResponse->get("code"));
		error(code);
		queueResponse = true;
	}
	else
	{
		queueResponse = true;
	}
	if (queueResponse)
	{
		_responseQueue.enqueueNotification(pResponse);
	}
}


BlueZGATTClient::ParsedResponse::Ptr BlueZGATTClient::expectResponse(const std::string& type, long timeout)
{
	ParsedResponse::Ptr pResponse = waitResponse(timeout);
	if (pResponse->type() == type)
	{
		return pResponse;
	}
	else if (pResponse->type() == "err")
	{
		std::string code = decodeValue(pResponse->get("code"));
		if (code == "connfail")
			throw Poco::IOException("cannot connect to peripheral");
		else if (code == "comerr")
			throw Poco::IOException("peripheral device error");
		else if (code == "protoerr")
			throw Poco::IOException("protocol error");
		else if (code == "notfound")
			throw Poco::IOException("not found");
		else if (code == "badcmd")
			throw Poco::IOException("bad command");
		else if (code == "badparam")
			throw Poco::IOException("bad parameter");
		else if (code == "badstate")
			throw Poco::IOException("bad state");
		else
			throw Poco::IOException(code);
	}
	else throw Poco::ProtocolException("unexpected type", pResponse->type());
}


BlueZGATTClient::ParsedResponse::Ptr BlueZGATTClient::waitResponse(long timeout)
{
	Poco::Notification* pNf = _responseQueue.waitDequeueNotification(timeout);
	if (pNf)
		return static_cast<ParsedResponse*>(pNf);
	else
		throw Poco::TimeoutException("timeout waiting for helper response");
}


void BlueZGATTClient::parseResponse(const std::string& response, ParsedResponse& parsedResponse)
{
	_logger.debug(Poco::format("[%s] Parsing response: %s", _address, response));

	// Note: later versions of bluepy-helper use ASCII RS (Record Separator, 0x1e)
	// instead of SPACE. We currently support both SPACE and RS.
	Poco::StringTokenizer tok(response, " \036", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if (tok.count() > 0)
	{
		for (Poco::StringTokenizer::Iterator it = tok.begin(); it != tok.end(); ++it)
		{
			const std::string& param = *it;
			std::string::size_type pos = param.find('=');
			if (pos != std::string::npos)
			{
				std::string key(param, 0, pos);
				std::string val(param, pos + 1);
				parsedResponse.add(KeyValuePair(key, val));
			}
			else throw Poco::SyntaxException("bad response parameter", param);
		}
	}
	else throw Poco::SyntaxException("bad response", response);
}


namespace
{
	Poco::UInt8 nibble(char hex)
	{
		if (hex >= 'a' && hex <= 'f')
			return hex - 'a' + 10;
		else if (hex >= 'A' && hex <= 'F')
			return hex - 'A' + 10;
		else if (hex >= '0' && hex <= '9')
			return hex - '0';
		else
			throw Poco::SyntaxException("invalid hex character");
	}
}


std::string BlueZGATTClient::decodeValue(const std::string& value)
{
	std::string decodedValue;
	if (!value.empty())
	{
		if (value[0] == '$' || value[0] == '\'')
		{
			decodedValue.assign(value, 1, std::string::npos);
		}
		else if (value[0] == 'h')
		{
			decodedValue.assign(value, 1, std::string::npos);
		}
		else if (value[0] == 'b')
		{
			std::string::size_type i = 1;
			while (i < value.size() - 1)
			{
				Poco::UInt8 byte = nibble(value[i++]) << 4;
				byte |= nibble(value[i++]);
				decodedValue += static_cast<char>(byte);
			}
		}
	}
	return decodedValue;
}


Poco::UInt16 BlueZGATTClient::decodeWord(const std::string& value)
{
	if (!value.empty() && value[0] == 'h')
	{
		std::string handle(value, 1, std::string::npos);
		return static_cast<Poco::UInt16>(Poco::NumberParser::parseHex(handle));
	}
	throw Poco::SyntaxException("expected handle value, got", value);
}


} } } // namespace IoT::BtLE::BlueZ
