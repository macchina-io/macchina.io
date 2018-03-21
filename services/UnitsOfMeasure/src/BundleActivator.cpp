//
// BundleActivator.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/ClassLibrary.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceServerHelper.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceImpl.h"
#include "IoT/UnitsOfMeasure/UCUMEssenceParser.h"
#include <memory>


namespace IoT {
namespace UnitsOfMeasure {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::UnitsOfMeasure::UnitsOfMeasureService> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		UnitsOfMeasureServiceImpl::Ptr pUoM = new UnitsOfMeasureServiceImpl;
		UCUMEssenceParser parser(*pUoM);
		std::unique_ptr<std::istream> istr(pContext->thisBundle()->getResource("ucum-essence.xml"));
		parser.parse(*istr);

		std::string oid("io.macchina.services.unitsofmeasure");
		ServerHelper::RemoteObjectPtr pRemoteObject = ServerHelper::createRemoteObject(pUoM, oid);
		_pServiceRef = pContext->registry().registerService(oid, pRemoteObject, Poco::OSP::Properties());
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef = 0;
		ServerHelper::shutdown();
	}

private:
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::UnitsOfMeasure


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::UnitsOfMeasure::BundleActivator)
POCO_END_MANIFEST
