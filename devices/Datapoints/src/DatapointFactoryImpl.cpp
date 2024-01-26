//
// DatapointFactoryImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  DatapointFactoryImpl
////
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/DatapointFactoryImpl.h"
#include "IoT/Datapoints/BooleanDatapointImpl.h"
#include "IoT/Devices/BooleanDatapointServerHelper.h"
#include "IoT/Datapoints/CounterDatapointImpl.h"
#include "IoT/Devices/CounterDatapointServerHelper.h"
#include "IoT/Datapoints/EnumDatapointImpl.h"
#include "IoT/Devices/EnumDatapointServerHelper.h"
#include "IoT/Datapoints/FlagsDatapointImpl.h"
#include "IoT/Devices/FlagsDatapointServerHelper.h"
#include "IoT/Datapoints/MovingAverageDatapointImpl.h"
#include "IoT/Datapoints/ScalarDatapointImpl.h"
#include "IoT/Devices/ScalarDatapointServerHelper.h"
#include "IoT/Datapoints/StringDatapointImpl.h"
#include "IoT/Devices/StringDatapointServerHelper.h"
#include "IoT/Datapoints/VectorDatapointImpl.h"
#include "IoT/Devices/VectorDatapointServerHelper.h"
#include "IoT/Devices/CompositeImpl.h"
#include "IoT/Devices/CompositeServerHelper.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/Format.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


DatapointFactoryImpl::DatapointFactoryImpl(Poco::OSP::BundleContext::Ptr pBundleContext):
	_pBundleContext(pBundleContext),
	_ids(ID_MAX)
{
}


DatapointFactoryImpl::~DatapointFactoryImpl()
{
	for (auto it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
	{
		_pBundleContext->registry().unregisterService(*it);
	}
}


template <typename ServiceType, typename ParamsType>
Poco::OSP::ServiceRef::Ptr DatapointFactoryImpl::createService(Poco::SharedPtr<ServiceType> pService, const std::string& id, const ParamsType& params)
{
	using ServerHelper = Poco::RemotingNG::ServerHelper<typename ServiceType::Interface>;

	typename ServerHelper::RemoteObjectPtr pServiceRemoteObject = ServerHelper::createRemoteObject(pService, id);

	Poco::OSP::Properties props;
	props.set("io.macchina.device"s, ServiceType::TYPE);
	props.set("io.macchina.deviceType"s, ServiceType::SYMBOLIC_NAME);
	props.set("io.macchina.datapoint"s, ServiceType::TYPE);
	if (!params.name.empty())
	{
		props.set("io.macchina.nodeName"s, params.name);
	}
	if (!params.composite.empty())
	{
		props.set("io.macchina.composite"s, params.composite);
	}
	for (const auto& t: params.tags)
	{
		props.set(t.name, t.value);
	}
	if (!params.customData.empty())
	{
		pService->setPropertyString("customData"s, params.customData);
	}
	return _pBundleContext->registry().registerService(id, pServiceRemoteObject, props);
}



DatapointFactory::ServiceID DatapointFactoryImpl::createBoolean(const BooleanDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, BooleanDatapointImpl::SYMBOLIC_NAME, createId(ID_BOOLEAN));
	auto pServiceRef = createService(Poco::makeShared<BooleanDatapointImpl>(id, params), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createCounter(const CounterDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, CounterDatapointImpl::SYMBOLIC_NAME, createId(ID_COUNTER));
	auto pServiceRef = createService(Poco::makeShared<CounterDatapointImpl>(id, params), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createEnum(const EnumDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, EnumDatapointImpl::SYMBOLIC_NAME, createId(ID_ENUM));
	auto pServiceRef = createService(Poco::makeShared<EnumDatapointImpl>(id, params), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createFlags(const FlagsDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, FlagsDatapointImpl::SYMBOLIC_NAME, createId(ID_FLAGS));
	auto pServiceRef = createService(Poco::makeShared<FlagsDatapointImpl>(id, params), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createMovingAverage(const MovingAverageDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, MovingAverageDatapointImpl::SYMBOLIC_NAME, createId(ID_MOVING_AVERAGE));
	auto pServiceRef = createService(Poco::makeShared<MovingAverageDatapointImpl>(id, params, _timer), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createScalar(const ScalarDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, ScalarDatapointImpl::SYMBOLIC_NAME, createId(ID_SCALAR));
	auto pServiceRef = createService(Poco::makeShared<ScalarDatapointImpl>(id, params, _timer), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createString(const StringDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, StringDatapointImpl::SYMBOLIC_NAME, createId(ID_STRING));
	auto pServiceRef = createService(Poco::makeShared<StringDatapointImpl>(id, params), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createVector(const VectorDatapointParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	const std::string id = Poco::format("%s#%u"s, VectorDatapointImpl::SYMBOLIC_NAME, createId(ID_VECTOR));
	auto pServiceRef = createService(Poco::makeShared<VectorDatapointImpl>(id, params), id, params);
	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


DatapointFactory::ServiceID DatapointFactoryImpl::createComposite(const CompositeParams& params)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::Devices::Composite>;

	auto id = createId(ID_COMPOSITE);
	std::string fullId = Poco::format("%s#%u"s, IoT::Devices::CompositeImpl::SYMBOLIC_NAME, id);

	auto pComposite = Poco::makeShared<IoT::Devices::CompositeImpl>(fullId, params.name, _pBundleContext->registry());
	ServerHelper::RemoteObjectPtr pCompositeRemoteObject = ServerHelper::createRemoteObject(pComposite, fullId);

	Poco::OSP::Properties props;
	props.set("io.macchina.device"s, IoT::Devices::CompositeImpl::TYPE);
	props.set("io.macchina.datapoint"s, IoT::Devices::CompositeImpl::TYPE);
	if (!params.name.empty())
	{
		props.set("io.macchina.nodeName"s, params.name);
	}
	if (!params.composite.empty())
	{
		props.set("io.macchina.composite"s, params.composite);
	}
	for (const auto& t: params.tags)
	{
		props.set(t.name, t.value);
	}

	auto pServiceRef = _pBundleContext->registry().registerService(fullId, pCompositeRemoteObject, props);

	_serviceRefs.push_back(pServiceRef);
	return pServiceRef->name();
}


void DatapointFactoryImpl::remove(const ServiceID serviceID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (auto it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
	{
		if ((*it)->name() == serviceID)
		{
			_pBundleContext->registry().unregisterService(*it);
			_serviceRefs.erase(it);
			return;
		}
	}
}


unsigned DatapointFactoryImpl::createId(unsigned type)
{
	poco_assert (type < _ids.size());

	return ++_ids[type];
}


} } // namespace IoT::Datapoints
