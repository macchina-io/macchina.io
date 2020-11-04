//
// JSBundleActivator.cpp
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "JSServletFilter.h"
#include "JSServerPageFilter.h"


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
		pContext->events().bundleStopping += Poco::delegate(this, &JSWebBundleActivator::onBundleStopping);
	}
		
	void stop(BundleContext::Ptr pContext)
	{	
		pContext->events().bundleStopping -= Poco::delegate(this, &JSWebBundleActivator::onBundleStopping);

		cleanupCache();
	}
	
protected:
	void onBundleStopping(const void*, BundleEvent& ev)
	{
		uncacheScripts(ev.bundle());
	}

	void uncacheScripts(Bundle::Ptr pBundle)
	{
		JSServletExecutorCache& cache = JSServletExecutorCache::instance();
		std::set<std::string> keys = cache.getAllKeys();
		for (std::set<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			JSServletExecutorHolder::Ptr pHolder = cache.get(*it);
			if (pHolder && pHolder->executor()->uri().getAuthority() == pBundle->symbolicName())
			{
				pHolder->executor()->stop();
				cache.remove(*it);
			}
		}
	}
	
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
