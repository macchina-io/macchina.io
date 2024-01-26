//
// BlueZPeripheralBrowser.cpp
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  BlueZPeripheralBrowser
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BlueZPeripheralBrowser.h"
#include "Poco/NumberFormatter.h"


using namespace std::string_literals;


namespace IoT {
namespace BtLE {
namespace BlueZ {


BlueZPeripheralBrowser::BlueZPeripheralBrowser(const std::string& helperPath):
	HelperClient(helperPath),
	_logger(Poco::Logger::get("IoT.BtLE.BlueZPeripheralBrowser"s))
{
}


BlueZPeripheralBrowser::~BlueZPeripheralBrowser()
{
}


void BlueZPeripheralBrowser::browse(bool activeScan)
{
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (_scanning && helperRunning()) throw Poco::IllegalStateException("scan already in progress");

		if (!helperRunning())
		{
			startHelper();
		}
		else if (_error)
		{
			_error = false;
			stopHelper();
			startHelper();
		}

		_activeScan = activeScan;
		if (activeScan)
		{
			sendCommand("scan"s);
		}
		else
		{
			sendCommand("pasv"s);
		}
		_scanning = true;
	}
}


void BlueZPeripheralBrowser::cancelBrowse()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (_scanning && helperRunning())
	{
		if (_activeScan)
		{
			sendCommand("scanend"s);
		}
		else
		{
			sendCommand("pasvend"s);
		}
	}
}


bool BlueZPeripheralBrowser::browseInProgress()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _scanning;
}


void BlueZPeripheralBrowser::processResponse(const std::string& response)
{
	if (!response.empty() && response[0] == '#') return;

	ParsedResponse::Ptr pResponse = new ParsedResponse;
	parseResponse(response, *pResponse);

	if (pResponse->type() == "scan")
	{
		std::string state = decodeValue(pResponse->get("state"s, ""s));
		if (state == "scan")
		{
			_logger.debug("Scan started."s);
			try
			{
				browseStarted(this);
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("browseStarted delegate leaked exception: %s"s, exc.displayText());
			}	
			catch (std::exception& exc)
			{
				_logger.error("browseStarted delegate leaked exception: %s"s, std::string(exc.what()));
			}
			catch (...)
			{
				_logger.error("browseStarted delegate leaked exception.");
			}
		}
		else if (state == "scanend")
		{
			if (_scanning)
			{
				_logger.debug("Scan completed."s);
				try
				{
					browseComplete(this);
				}
				catch (Poco::Exception& exc)
				{
					_logger.error("browseComplete delegate leaked exception: %s"s, exc.displayText());
				}	
				catch (std::exception& exc)
				{
					_logger.error("browseComplete delegate leaked exception: %s"s, std::string(exc.what()));
				}
				catch (...)
				{
					_logger.error("browseComplete delegate leaked exception.");
				}
				_scanning = false;			
			}
		}
		else if (_scanning)
		{
			std::string address = decodeValue(pResponse->get("addr"s));
			std::string data = decodeValue(pResponse->get("d"s, ""s));
			Poco::UInt16 type = decodeWord(pResponse->get("type"s));
			Poco::UInt16 rssi = decodeWord(pResponse->get("rssi"s));
			Poco::UInt32 flags = decodeWord32(pResponse->get("flag"s));

			PeripheralInfo pinfo;
			pinfo.address = formatAddress(address);
			pinfo.addressType = static_cast<AddressType>(type);
			pinfo.name = extractName(data);
			pinfo.connectable = (flags & 0x04) == 0;
			pinfo.rssi = -rssi;
			pinfo.data = splitData(data);

			_logger.debug("Peripheral found: %s (%s)"s, pinfo.address, pinfo.name);

			try
			{
				peripheralFound(this, pinfo);
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("peripheralFound delegate leaked exception: %s"s, exc.displayText());
			}	
			catch (std::exception& exc)
			{
				_logger.error("peripheralFound delegate leaked exception: %s"s, std::string(exc.what()));
			}
			catch (...)
			{
				_logger.error("peripheralFound delegate leaked exception.");
			}
		}
		else
		{
			_logger.warning("Unexpected scan message received."s);
		}	
	}
	else if (pResponse->type() == "err")
	{
		std::string code = decodeValue(pResponse->get("code"s));
		std::string msg = decodeValue(pResponse->get("emsg"s, std::string()));
		if (!msg.empty())
		{
			code += ": ";
			code += msg;
		}
		_logger.error("Scan error: %s"s, code);
		try
		{
			browseError(this, code);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("browseError delegate leaked exception: %s"s, exc.displayText());
		}	
		catch (std::exception& exc)
		{
			_logger.error("browseError delegate leaked exception: %s"s, std::string(exc.what()));
		}
		catch (...)
		{
			_logger.error("browseError delegate leaked exception.");
		}
		_scanning = false;
		_error = true;
	}
}


std::string BlueZPeripheralBrowser::formatAddress(const std::string& binaryAddress)
{
	std::string formatted;
	for (const auto b: binaryAddress)
	{
		if (!formatted.empty()) formatted += ':';
		Poco::NumberFormatter::appendHex(formatted, static_cast<unsigned>(static_cast<unsigned char>(b)), 2);
	}
	return formatted;
}


std::string BlueZPeripheralBrowser::extractName(const std::string& data)
{
	std::string name;
	std::size_t i = 0;
	std::size_t total = data.size();
	while (i < total)
	{
		std::size_t len = static_cast<std::size_t>(static_cast<unsigned char>(data[i]));
		i++;
		if (i < total)
		{
			char type = data[i];
			if (type == AD_TYPE_COMPLETE_LOCAL_NAME || type == AD_TYPE_SHORTENED_LOCAL_NAME)
			{
				len--; i++;
				while (i < total && len > 0)
				{
					name += data[i];
					i++; len--;
				}
				break;
			}
			else
			{
				i += len;
			}
		}
	}
	return name;
}


std::vector<AdvertisingData> BlueZPeripheralBrowser::splitData(const std::string& data)
{
	std::vector<AdvertisingData> fields;
	std::size_t i = 0;
	std::size_t total = data.size();
	while (i < total)
	{
		std::size_t len = static_cast<std::size_t>(static_cast<unsigned char>(data[i]));
		i++;
		if (i < total)
		{
			AdvertisingData field;
			field.type = static_cast<Poco::UInt8>(data[i]);
			len--; i++;
			field.data.reserve(len);
			while (i < total && len > 0)
			{
				field.data.push_back(data[i]);
				i++; len--;
			}
			fields.push_back(std::move(field));
		}
	}
	return fields;
}


} } } // namespace IoT::BtLE::BlueZ
