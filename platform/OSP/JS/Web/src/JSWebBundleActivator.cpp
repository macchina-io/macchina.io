//
// JSBundleActivator.cpp
//
// $Id: //poco/1.4/OSP/JS/src/JSBundleActivator.cpp#6 $
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/JS/Bridge/Listener.h"
#include "Poco/JS/Bridge/BridgeWrapper.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/OSP/JS/JSExtensionPoint.h"
#include "JSServletFilter.h"
#include "JSServerPageFilter.h"
#include "v8.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSWebBundleActivator: public Poco::OSP::BundleActivator
{
public:
	JSWebBundleActivator()
	{
	}
	
	~JSWebBundleActivator()
	{
	}
	
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{

	}
		
	void stop(BundleContext::Ptr pContext)
	{	
		cleanupCache();
	}
	
protected:
	void cleanupCache()
	{
		JSServletExecutorCache& cache = JSServletExecutorCache::instance();
		std::set<std::string> keys = cache.getAllKeys();
		for (std::set<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			JSServletExecutorHolder::Ptr pHolder = cache.get(*it);
			if (pHolder)
			{
				pHolder->executor()->stop();
			}
		}
		JSServletExecutorCache::instance().clear();
	}
};


} } } } // namespace Poco::OSP::JS::Web


POCO_BEGIN_NAMED_MANIFEST(WebFilter, Poco::OSP::Web::WebFilterFactory)
	POCO_EXPORT_CLASS(Poco::OSP::JS::Web::JSServletFilterFactory)
	POCO_EXPORT_CLASS(Poco::OSP::JS::Web::JSServerPageFilterFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Poco::OSP::JS::Web::JSWebBundleActivator)
POCO_END_MANIFEST
