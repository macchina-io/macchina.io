//
// HelperClient.cpp
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  HelperClient
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "HelperClient.h"
#include "Poco/StringTokenizer.h"
#include "Poco/File.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"


using namespace std::string_literals;


namespace IoT {
namespace BtLE {
namespace BlueZ {


HelperClient::HelperClient(const std::string helperPath):
	_helperPath(helperPath),
	_logger(Poco::Logger::get("IoT.BtLE.HelperClient"s))
{
}


HelperClient::~HelperClient()
{
	try
	{
		stopHelper();
	}
	catch (...)
	{
	}	
}


void HelperClient::startHelper()
{
	if (!_pHelperInfo)
	{
		_logger.debug("Starting helper: %s..."s, _helperPath);
		Poco::File helperExec(_helperPath);
		if (!helperExec.exists())
			throw Poco::FileNotFoundException("helper executable not found"s, _helperPath);
		if (!helperExec.canExecute())
			throw Poco::FileException("helper executable does not have execute permission"s, _helperPath);

		Poco::Pipe inputPipe;
		Poco::Pipe outputPipe;
		Poco::Process::Args args;
		Poco::ProcessHandle ph = Poco::Process::launch(_helperPath, args, &inputPipe, &outputPipe, 0);
		_pHelperInfo = new HelperInfo(ph, inputPipe, outputPipe);
		_helperThread.start(*this);
		_logger.debug("Helper started."s);
	}
}


void HelperClient::stopHelper()
{
	if (_pHelperInfo)
	{
		_logger.debug("Stopping helper..."s);
		if (helperRunning())
		{
			try
			{
				sendCommand("quit"s);
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
			_logger.debug("Helper failed to quit in time, killing..."s);
			Poco::Process::kill(_pHelperInfo->processHandle);
			try
			{
				_helperThread.join();
			}
			catch (Poco::Exception& exc)
			{
				_logger.debug("Failed to join helper thread: %s"s, exc.displayText());
			}
		}
		_pHelperInfo.reset();
		_logger.debug("Helper stopped."s);
	}
}


bool HelperClient::helperRunning()
{
	return _pHelperInfo && _pHelperInfo->outputStream.good();
}


void HelperClient::run()
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
	_logger.debug("Helper process terminated"s);
	try
	{
		 _pHelperInfo->processHandle.wait();
	}
	catch (Poco::Exception& exc)
	{
		_logger.debug("Failed to wait for helper process: %s"s, exc.displayText());
	}
}


void HelperClient::sendCommand(const std::string& command)
{
	if (helperRunning())
	{
		_logger.debug("Sending command: %s"s, command);

		if (!_responseQueue.empty())
		{
			_logger.debug("Response queue not empty"s);
			_responseQueue.clear();
		}

		_pHelperInfo->outputStream << command << std::endl;
		if (!_pHelperInfo->outputStream.good())
		{
			_pHelperInfo = 0;
			throw Poco::IOException("helper process no longer running"s);
		}
	}
	else throw Poco::IllegalStateException("helper process not running"s);
}


HelperClient::ParsedResponse::Ptr HelperClient::expectResponse(const std::string& type, long timeout)
{
	ParsedResponse::Ptr pResponse = waitResponse(timeout);
	if (pResponse->type() == type)
	{
		return pResponse;
	}
	else if (pResponse->type() == "err")
	{
		std::string code = decodeValue(pResponse->get("code"s));
		std::string msg = decodeValue(pResponse->get("emsg"s, std::string()));
		if (code == "connfail")
			throw Poco::IOException("cannot connect to peripheral"s, msg);
		else if (code == "comerr")
			throw Poco::IOException("peripheral device error"s, msg);
		else if (code == "protoerr")
			throw Poco::IOException("protocol error"s, msg);
		else if (code == "notfound")
			throw Poco::IOException("not found"s, msg);
		else if (code == "badcmd")
			throw Poco::IOException("bad command"s, msg);
		else if (code == "badparam")
			throw Poco::IOException("bad parameter"s, msg);
		else if (code == "badstate")
			throw Poco::IOException("bad state"s, msg);
		else
			throw Poco::IOException(code, msg);
	}
	else throw Poco::ProtocolException("unexpected type"s, pResponse->type());
}


HelperClient::ParsedResponse::Ptr HelperClient::waitResponse(long timeout)
{
	Poco::Notification* pNf = _responseQueue.waitDequeueNotification(timeout);
	if (pNf)
		return static_cast<ParsedResponse*>(pNf);
	else
		throw Poco::TimeoutException("timeout waiting for helper response"s);
}


void HelperClient::parseResponse(const std::string& response, ParsedResponse& parsedResponse)
{
	_logger.debug("Parsing response: %s"s, response);

	std::string delim;
	if (response.find('\036') != std::string::npos)
		delim = "\036";
	else
		delim = " ";
	Poco::StringTokenizer tok(response, delim, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
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
			else throw Poco::SyntaxException("bad response parameter"s, param);
		}
	}
	else throw Poco::SyntaxException("bad response"s, response);
}


void HelperClient::enqueueResponse(ParsedResponse::Ptr pResponse)
{
	_responseQueue.enqueueNotification(pResponse);
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


std::string HelperClient::decodeValue(const std::string& value)
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


Poco::UInt16 HelperClient::decodeWord(const std::string& value)
{
	if (!value.empty() && value[0] == 'h')
	{
		std::string hex(value, 1, std::string::npos);
		return static_cast<Poco::UInt16>(Poco::NumberParser::parseHex(hex));
	}
	throw Poco::SyntaxException("expected hex, got"s, value);
}


Poco::UInt32 HelperClient::decodeWord32(const std::string& value)
{
	if (!value.empty() && value[0] == 'h')
	{
		std::string hex(value, 1, std::string::npos);
		return Poco::NumberParser::parseHex(hex);
	}
	throw Poco::SyntaxException("expected hex value, got"s, value);
}


} } } // namespace IoT::BtLE::BlueZ
