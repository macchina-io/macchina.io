//
// PooledIsolate.h
//
// Library: JS/Core
// Package: Execution
// Module:  IsolatePool
//
// Definition of the IsolatePool class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_PooledIsolate_INCLUDED
#define JS_Core_PooledIsolate_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/ObjectPool.h"
#include "v8.h"
#include <map>


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API PooledIsolate
{
public:
	using Pool = Poco::ObjectPool<PooledIsolate>;

	enum
	{
		MINIMUM_MEMORY_LIMIT = 8*1024*1024
	};

	explicit PooledIsolate(Poco::UInt64 memoryLimit);
		/// Creates the PooledIsolate with the given memoryLimit.

	~PooledIsolate();
		/// Destroys the PooledIsolate.

	v8::Isolate* isolate() const;
		/// Returns the underlying v8::Isolate.

	static PooledIsolate* fromIsolate(v8::Isolate* pIsolate);
		/// Returns the PooledIsolate for the given Isolate.

	v8::Persistent<v8::ObjectTemplate>& objectTemplate(const std::string& name);
		/// Returns the persistent handle for the object template with the given name.

protected:
	static std::size_t onNearHeapLimit(void* data, std::size_t currentHeapLimit, std::size_t initialHeapLimit);

private:
	PooledIsolate();
	PooledIsolate(const PooledIsolate&);
	PooledIsolate& operator = (const PooledIsolate&);

	class JSCore_API OTHolder
	{
	public:
		OTHolder()
		{
		}

		OTHolder(const OTHolder& other)
		{
			_ot.Reset(v8::Isolate::GetCurrent(), other._ot);
		}

		~OTHolder()
		{
			_ot.Reset();
		}

		OTHolder& operator = (const OTHolder& other)
		{
			if (this != &other)
			{
				_ot.Reset(v8::Isolate::GetCurrent(), other._ot);
			}
			return *this;
		}

		v8::Persistent<v8::ObjectTemplate>& content()
		{
			return _ot;
		}

	private:
		v8::Persistent<v8::ObjectTemplate> _ot;
	};

	using OTMap = std::map<std::string, OTHolder>;

	v8::Isolate* _pIsolate;
	v8::ArrayBuffer::Allocator* _pArrayBufferAllocator;
	Poco::UInt64 _memoryLimit;
	OTMap _objectTemplates;
};


//
// inlines
//


inline v8::Isolate* PooledIsolate::isolate() const
{
	return _pIsolate;
}


} } } // namespace Poco::JS::Core


#endif // JS_Core_PooledIsolate_INCLUDED
