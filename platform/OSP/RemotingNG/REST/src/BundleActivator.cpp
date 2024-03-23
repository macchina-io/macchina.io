//
// BundleActivator.cpp
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/RemotingNG/REST/TransportFactory.h"
#include "Poco/RemotingNG/REST/Transport.h"
#include "Poco/Net/HTTPSSessionInstantiator.h"
#include "Poco/ClassLibrary.h"


namespace Poco {
namespace OSP {
namespace RemotingNG {
namespace REST {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		Poco::RemotingNG::REST::TransportFactory::registerFactory();
		Poco::RemotingNG::REST::Transport::httpSessionFactory().registerProtocol(
			"https",
			new Poco::Net::HTTPSSessionInstantiator
		);
	}

	void stop(BundleContext::Ptr pContext)
	{
		Poco::RemotingNG::REST::TransportFactory::unregisterFactory();
		Poco::RemotingNG::REST::Transport::httpSessionFactory().unregisterProtocol("https");
	}
};


} } } } // namespace Poco::OSP::RemotingNG::REST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Poco::OSP::RemotingNG::REST::BundleActivator)
POCO_END_MANIFEST
