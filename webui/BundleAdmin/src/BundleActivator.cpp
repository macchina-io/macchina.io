//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Exception.h"
#include "Poco/ClassLibrary.h"
#include "BundleRequestHandler.h"
#include "BundleListRequestHandler.h"
#include "BundleActionsRequestHandler.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


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


} } } // namespace IoT::Web::BundleAdmin


POCO_BEGIN_NAMED_MANIFEST(WebServer, Poco::OSP::Web::WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::BundleAdmin::BundleRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::BundleAdmin::BundleListRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::BundleAdmin::BundleActionsRequestHandlerFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Web::BundleAdmin::BundleActivator)
POCO_END_MANIFEST
