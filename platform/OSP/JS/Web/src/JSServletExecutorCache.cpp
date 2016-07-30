//
// JSServletExecutorCache.cpp
//
// $Id$
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "JSServletExecutorCache.h"


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


} } } } // namespace Poco::OSP::JS::Web
