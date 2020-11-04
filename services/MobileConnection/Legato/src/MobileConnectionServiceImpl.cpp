//
// MobileConnectionServiceImpl.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "MobileConnectionServiceImpl.h"
#include "Poco/Process.h"
#include "Poco/Pipe.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Exception.h"
#include "Poco/String.h"


namespace IoT {
namespace MobileConnection {
namespace Legato {


const std::string MobileConnectionServiceImpl::DEFAULT_CM_PATH("/legato/systems/current/bin/cm");


class DataConnectionHandler: public Poco::Runnable
{
public:
	DataConnectionHandler(MobileConnectionServiceImpl& mcsImpl, const std::string& cmPath):
		_mcsImpl(mcsImpl),
		_cmPath(cmPath),
		_outputPipe(),
		_ph(launch(cmPath, _outputPipe)),
		_joined(false),
		_logger(Poco::Logger::get("IoT.MobileConnection.Legato.DataConnectionHandler"))
	{
		_thread.start(*this);
	}

	~DataConnectionHandler()
	{
		try
		{
			stop();
		}
		catch (...)
		{
		}
	}

	void stop()
	{
		if (!_joined)
		{
			if (_thread.isRunning())
			{
				Poco::Process::requestTermination(_ph.id());
			}

			if (!_thread.tryJoin(5000))
			{
				_logger.notice("%s not responding to SIGINT, killing.", _cmPath);
				Poco::Process::kill(_ph);
				_thread.join();
			}
			_joined = true;
		}
	}

	bool isDead()
	{
		return !_thread.isRunning();
	}

	void run()
	{
		try
		{
			Poco::PipeInputStream istr(_outputPipe);
			std::string line;
			std::getline(istr, line);
			_logger.debug("Received status line: %s", line);
			if (line.find("Connected") != std::string::npos)
			{
				_mcsImpl.fireDataConnected();
			}
			int ch = istr.get();
			while (ch != -1) ch = istr.get();
			int rc = _ph.wait();
			_logger.debug("DataConnectionHandler: %s exited with %d.", _cmPath, rc);

			_mcsImpl.fireDataDisconnected();
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}

protected:
	static Poco::ProcessHandle launch(const std::string& cmPath, Poco::Pipe& pipe)
	{
		std::vector<std::string> args;
		args.push_back("data");
		args.push_back("connect");
		return Poco::Process::launch(cmPath, args, 0, &pipe, 0);
	}

private:
	MobileConnectionServiceImpl& _mcsImpl;
	std::string _cmPath;
	Poco::Pipe _outputPipe;
	Poco::ProcessHandle _ph;
	Poco::Thread _thread;
	bool _joined;
	Poco::Logger& _logger;
};


MobileConnectionServiceImpl::MobileConnectionServiceImpl(const std::string& cmPath):
	_cmPath(cmPath),
	_cmCache(2500),
	_logger(Poco::Logger::get("IoT.MobileConnection.Legato"))
{
}


MobileConnectionServiceImpl::~MobileConnectionServiceImpl()
{
}


std::string MobileConnectionServiceImpl::imei() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("info", "all");
	return extractValue(result, "IMEI");
}


std::string MobileConnectionServiceImpl::deviceName() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("info", "all");
	return extractValue(result, "Device");
}


SIMState MobileConnectionServiceImpl::simState() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("sim", "status");
	if (result.find("LE_SIM_INSERTED") != std::string::npos)
		return MC_SIM_INSERTED;
	else if (result.find("LE_SIM_ABSENT") != std::string::npos)
		return MC_SIM_ABSENT;
	else if (result.find("LE_SIM_READY") != std::string::npos)
		return MC_SIM_READY;
	else if (result.find("LE_SIM_BLOCKED") != std::string::npos)
		return MC_SIM_BLOCKED;
	else if (result.find("LE_SIM_BUSY") != std::string::npos)
		return MC_SIM_BUSY;
	else
		return MC_SIM_UNKNOWN;
}


void MobileConnectionServiceImpl::unlockSIM(const std::string& pin)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	cm("sim", "unlock", pin);
	_cmCache.remove("sim:status");
}


void MobileConnectionServiceImpl::lockSIM(const std::string& pin)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	cm("sim", "lock", pin);
	_cmCache.remove("sim:status");
}


void MobileConnectionServiceImpl::enterPIN(const std::string& pin)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	cm("sim", "enterpin", pin);
	_cmCache.remove("sim:status");
}


std::string MobileConnectionServiceImpl::imsi() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("sim", "info");
	return extractValue(result, "IMSI");
}


std::string MobileConnectionServiceImpl::phoneNumber() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("sim", "info");
	return extractValue(result, "Phone Number");
}


std::string MobileConnectionServiceImpl::iccid() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("sim", "info");
	return extractValue(result, "ICCID");
}


void MobileConnectionServiceImpl::setAPN(const std::string& apn)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	cm("data", "apn", apn);
	_cmCache.remove("data:info");
}


std::string MobileConnectionServiceImpl::getAPN() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("data", "info");
	return extractValue(result, "APN");
}


void MobileConnectionServiceImpl::setPDPType(PDPType type)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string t;
	switch (type)
	{
	case MC_PDP_IPV4:
		t = "IPV4";
	case MC_PDP_IPV6:
		t = "IPV6";
	case MC_PDP_IPV4V6:
		t = "IPV4V6";
	default:
		throw Poco::InvalidArgumentException("PDPType");
	}
	cm("data", "pdp", t);
	_cmCache.remove("data:info");
}


PDPType MobileConnectionServiceImpl::getPDPType() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("data", "info");
	std::string type = extractValue(result, "PDP Type");
	if (type == "IPV4")
		return MC_PDP_IPV4;
	else if (type == "IPV6")
		return MC_PDP_IPV6;
	else if (type == "IPV4V6")
		return MC_PDP_IPV4V6;
	else
		return MC_PDP_UNKNOWN;
}


void MobileConnectionServiceImpl::authenticate(AuthMethod method, const std::string& username, const std::string& password)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::vector<std::string> args;
	args.push_back("data");
	args.push_back("auth");

	switch (method)
	{
	case MC_AUTH_NONE:
		args.push_back("none");
		break;
	case MC_AUTH_PAP:
		args.push_back("pap");
		break;
	case MC_AUTH_CHAP:
		args.push_back("chap");
		break;
	default:
		throw Poco::InvalidArgumentException("AuthMethod", method);
	}

	args.push_back(username);
	args.push_back(password);

	cm(args);
}


void MobileConnectionServiceImpl::enableRadio(bool enable)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	cm("radio", enable ? "on" : "off");
	_cmCache.remove("radio:status");
}


bool MobileConnectionServiceImpl::isRadioEnabled() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	try
	{
		std::string result = cmCached("radio", "status");
		return extractValue(result, "Power") == "ON";
	}
	catch (Poco::Exception&)
	{
		return false;
	}
}


std::string MobileConnectionServiceImpl::networkOperator() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("radio", "status");
	return extractValue(result, "Current Network Operator");
}


RegistrationStatus MobileConnectionServiceImpl::registrationStatus() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("radio", "status");
	std::string status = extractValue(result, "Status");
	if (status.find("LE_MRC_REG_NONE") != std::string::npos)
		return MC_REG_NONE;
	else if (status.find("LE_MRC_REG_HOME") != std::string::npos)
		return MC_REG_HOME;
	else if (status.find("LE_MRC_REG_SEARCHING") != std::string::npos)
		return MC_REG_SEARCHING;
	else if (status.find("LE_MRC_REG_DENIED") != std::string::npos)
		return MC_REG_DENIED;
	else if (status.find("LE_MRC_REG_ROAMING") != std::string::npos)
		return MC_REG_ROAMING;
	else
		return MC_REG_UNKNOWN;
}


RadioAccessTechnology MobileConnectionServiceImpl::radioAccessTechnology() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("radio", "status");
	std::string status = extractValue(result, "RAT");
	if (status.find("LE_MRC_RAT_CDMA") != std::string::npos)
		return MC_RAT_CDMA;
	else if (status.find("LE_MRC_RAT_GSM") != std::string::npos)
		return MC_RAT_GSM;
	else if (status.find("LE_MRC_RAT_UMTS") != std::string::npos)
		return MC_RAT_UMTS;
	else if (status.find("LE_MRC_RAT_LTE") != std::string::npos)
		return MC_RAT_LTE;
	else if (status.find("LE_MRC_RAT_TDSCDMA") != std::string::npos)
		return MC_RAT_TDSCDMA;
	else
		return MC_RAT_UNKNOWN;
}


int MobileConnectionServiceImpl::signalStrength() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("radio", "status");
	std::string status = extractValue(result, "Signal");
	if (status.find("(0)") != std::string::npos)
		return 0;
	else if (status.find("(1)") != std::string::npos)
		return 1;
	else if (status.find("(2)") != std::string::npos)
		return 2;
	else if (status.find("(3)") != std::string::npos)
		return 3;
	else if (status.find("(4)") != std::string::npos)
		return 4;
	else if (status.find("(5)") != std::string::npos)
		return 5;
	else
		return -1;
}


bool MobileConnectionServiceImpl::isDataConnected()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string result = cmCached("data", "info");
	return extractValue(result, "Connected") == "yes";
}


void MobileConnectionServiceImpl::connectData()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!_pDataConnectionHandler || _pDataConnectionHandler->isDead())
	{
		_pDataConnectionHandler = new DataConnectionHandler(*this, _cmPath);
	}
	else throw Poco::IllegalStateException("Data connection already in progress");
}


void MobileConnectionServiceImpl::disconnectData()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_pDataConnectionHandler = 0;
}


std::string MobileConnectionServiceImpl::cmCached(const std::string& module, const std::string& command) const
{
	std::string key(module);
	key += ":";
	key += command;
	Poco::SharedPtr<std::string> pCached = _cmCache.get(key);
	if (pCached)
	{
		return *pCached;
	}
	else
	{
		std::string value = cm(module, command);
		_cmCache.add(key, value);
		return value;
	}
}


std::string MobileConnectionServiceImpl::cm(const std::string& module, const std::string& command) const
{
	std::vector<std::string> args;
	args.push_back(module);
	args.push_back(command);
	return cm(args);
}


std::string MobileConnectionServiceImpl::cm(const std::string& module, const std::string& command, const std::string& arg) const
{
	std::vector<std::string> args;
	args.push_back(module);
	args.push_back(command);
	args.push_back(arg);
	return cm(args);
}


std::string MobileConnectionServiceImpl::cm(const std::vector<std::string>& args) const
{
	Poco::Pipe outputPipe;
	Poco::ProcessHandle ph = Poco::Process::launch(_cmPath, args, 0, &outputPipe, &outputPipe);
	Poco::PipeInputStream istr(outputPipe);
	std::string output;
	Poco::StreamCopier::copyToString(istr, output);
	int rc = ph.wait();
	if (rc != 0) throw Poco::RuntimeException("Failed to execute cm", output);
	return output;
}


std::string MobileConnectionServiceImpl::extractValue(const std::string& values, const std::string& key)
{
	std::string value;
	std::string label(key);
	label += ":";
	std::string::size_type pos1 = values.find(label);
	if (pos1 != std::string::npos)
	{
		pos1 += label.size();
		std::string::size_type pos2 = values.find('\n', pos1);
		if (pos2 != std::string::npos)
		{
			value = Poco::trim(values.substr(pos1, pos2 - pos1));
		}
	}
	return value;
}


void MobileConnectionServiceImpl::fireDataConnected()
{
	try
	{
		_logger.information("Data connection opened.");
		dataConnected(this);
	}
	catch (Poco::Exception&)
	{
	}
}


void MobileConnectionServiceImpl::fireDataDisconnected()
{
	try
	{
		_logger.information("Data connection closed.");
		dataDisconnected(this);
	}
	catch (Poco::Exception&)
	{
	}
}


} } } // namespace IoT::MobileConnection::Legato
