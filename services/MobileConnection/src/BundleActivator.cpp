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
#include "Poco/ClassLibrary.h"


namespace IoT {
namespace MobileConnection {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
	}
};


} } // namespace IoT::MobileConnection


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::MobileConnection::BundleActivator)
POCO_END_MANIFEST
