//
// JSServletExecutorCache.h
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_ServletExecutorCache_INCLUDED
#define OSP_JS_ServletExecutorCache_INCLUDED


#include "JSServletExecutor.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include "Poco/LRUCache.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSServletExecutorHolder
	/// Helper class for storing JSServletExecutor objects in a shared cache.
{
public:
	using Ptr = Poco::SharedPtr<JSServletExecutorHolder>;

	JSServletExecutorHolder(JSServletExecutor::Ptr pExecutor);
		/// Creates the JSServletExecutorHolder.

	JSServletExecutor::Ptr executor()
		/// Returns the held JSServletExecutor.
	{
		return _pExecutor;
	}

	void lock()
		/// Locks access to the instance.
	{
		_mutex.lock();
	}

	void lock(long timeout)
	{
		_mutex.lock(timeout);
	}

	void unlock()
		/// Unlocks access to the instance.
	{
		_mutex.unlock();
	}

private:
	JSServletExecutor::Ptr _pExecutor;
	Poco::FastMutex _mutex;
};


class JSServletExecutorCache: public Poco::LRUCache<std::string, JSServletExecutorHolder, Poco::Mutex>
	/// Shared cache for JSServletExecutor objects.
{
public:
	JSServletExecutorCache(long size = 256);
		/// Creates the JSServletExecutorCache.

	void lock()
		/// Locks access to the instance.
	{
		_mutex.lock();
	}

	void unlock()
		/// Unlocks access to the instance.
	{
		_mutex.unlock();
	}

	static JSServletExecutorCache& instance();
		/// Returns the shared instance of the JSServletExecutorCache.
};


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_ServletExecutorCache_INCLUDED
