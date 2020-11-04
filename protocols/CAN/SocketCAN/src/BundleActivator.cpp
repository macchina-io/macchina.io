//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "CANEndpointImpl.h"
#include "IoT/CAN/CANEndpointServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/StringTokenizer.h"
#include "Poco/String.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace CAN {
namespace SocketCAN {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::CAN::CANEndpoint> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	CANEndpoint::Ptr createCANEndpoint(const std::string& id, const std::string& interfc)
	{
		CANEndpoint::Ptr pCANEndpoint = new CANEndpointImpl(interfc);
		std::string symbolicName = "io.macchina.can.socketcan";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += id;
		ServerHelper::RemoteObjectPtr pCANEndpointRemoteObject = ServerHelper::createRemoteObject(pCANEndpoint, oid);

		Properties props;
		props.set("io.macchina.protocol", symbolicName);
		props.set("io.macchina.can.device", interfc);
		props.set("io.macchina.can.id", id);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pCANEndpointRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);

		return pCANEndpoint;
	}

	Poco::UInt32 parseUInt32(const std::string& value)
	{
		if (value.compare(0, 2, "0x") == 0)
			return Poco::NumberParser::parseHex(value);
		else
			return Poco::NumberParser::parseUnsigned(value);
	}

	std::vector<Poco::UInt32> parseIDs(const std::string& idString)
	{
		std::vector<Poco::UInt32> result;
		Poco::StringTokenizer tok(idString, ",;", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
		for (Poco::StringTokenizer::Iterator it = tok.begin(); it != tok.end(); ++it)
		{
			std::string::size_type pos = it->find('-');
			if (pos != std::string::npos)
			{
				Poco::UInt32 from = parseUInt32(it->substr(0, pos));
				Poco::UInt32 to   = parseUInt32(it->substr(pos + 1));
				for (Poco::UInt32 i = from; i <= to; i++)
				{
					result.push_back(i);
				}
			}
			else
			{
				result.push_back(parseUInt32(*it));
			}
		}
		return result;
	}

	std::vector<Filter> configureFilter(const std::string& baseKey)
	{
		std::vector<Filter> filter;
		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys(baseKey, keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string key(baseKey);
			key += ".";
			key += *it;

			Filter f;
			f.mask = _pPrefs->configuration()->getUInt(key + ".mask", Filter::CAN_FILTER_MASK_SFF);
			f.invert = _pPrefs->configuration()->getBool(key + ".invert", false);
			std::string idString = _pPrefs->configuration()->getString(key + ".id");
			std::vector<Poco::UInt32> ids = parseIDs(idString);
			for (std::vector<Poco::UInt32>::const_iterator itID = ids.begin(); itID != ids.end(); ++itID)
			{
				f.id = *itID;
				filter.push_back(f);
			}
		}
		return filter;
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("socketcan.endpoints", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "socketcan.endpoints.";
			baseKey += *it;

			const std::string interfc = _pPrefs->configuration()->getString(baseKey + ".interface", "");
			const bool enableEvents = _pPrefs->configuration()->getBool(baseKey + ".events.enable", false);
			const bool enableFD = _pPrefs->configuration()->getBool(baseKey + ".canfd.enable", false);
			const std::string filterMode = Poco::toLower(_pPrefs->configuration()->getString(baseKey + ".filter.mode", "or"));
			if (filterMode != "and" && filterMode != "or")
			{
				pContext->logger().warning("Invalid filter mode specified. Must be 'or' or 'and', but is '%s'. Using default 'or'.", filterMode);
			}

			try
			{
				pContext->logger().information(Poco::format("Creating SocketCAN CANEndpoint for interface %s.", interfc));
				CANEndpoint::Ptr pEndpoint = createCANEndpoint(*it, interfc);
				pEndpoint->enableEvents(enableEvents);
				pEndpoint->enableFD(enableFD);
				pEndpoint->setFilter(configureFilter(baseKey + ".filter"));
				pEndpoint->setFilterMode(filterMode == "and" ? CAN_FILTER_MODE_AND : CAN_FILTER_MODE_OR);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create SocketCAN CANEndpoint for interface %s: %s", interfc, exc.displayText()));
			}
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();
		_pPrefs = 0;
		_pContext = 0;

		ServerHelper::shutdown();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::CAN::SocketCAN


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::CAN::SocketCAN::BundleActivator)
POCO_END_MANIFEST
