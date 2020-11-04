//
// JSServletExecutorCache.cpp
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JSServletExecutorCache.h"
#include "Poco/SingletonHolder.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


//
// JSServletExecutorHolder
//


JSServletExecutorHolder::JSServletExecutorHolder(JSServletExecutor::Ptr pExecutor):
	_pExecutor(pExecutor)
{
}


//
// JSServletExecutorCache
//


JSServletExecutorCache::JSServletExecutorCache(long size):
	Poco::LRUCache<std::string, JSServletExecutorHolder, Poco::Mutex>(size)
{
}


namespace
{
	static Poco::SingletonHolder<JSServletExecutorCache> sh;
}


JSServletExecutorCache& JSServletExecutorCache::instance()
{
	return *sh.get();
}


} } } } // namespace Poco::OSP::JS::Web
