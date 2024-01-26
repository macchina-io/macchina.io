//
// PooledIsolate.cpp
//
// Library: JS/Core
// Package: Execution
// Module:  IsolatePool
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/JSException.h"
#include <algorithm>
#include <cstdlib>


namespace Poco {
namespace JS {
namespace Core {


PooledIsolate::PooledIsolate(Poco::UInt64 memoryLimit):
	_pIsolate(0),
	_pArrayBufferAllocator(v8::ArrayBuffer::Allocator::NewDefaultAllocator()),
	_memoryLimit(std::max(memoryLimit, Poco::UInt64(MINIMUM_MEMORY_LIMIT)))
{
	v8::Isolate::CreateParams params;
	params.constraints.ConfigureDefaultsFromHeapSize(0, _memoryLimit);
	params.array_buffer_allocator = _pArrayBufferAllocator;
	_pIsolate = v8::Isolate::New(params);
	if (!_pIsolate) throw JSException("Cannot create isolate");
	_pIsolate->SetData(0, this);
	_pIsolate->AddNearHeapLimitCallback(onNearHeapLimit, _pIsolate);
	_pIsolate->AutomaticallyRestoreInitialHeapLimit(0.5);
	_pIsolate->SetCaptureStackTraceForUncaughtExceptions(true, 16, v8::StackTrace::kDetailed);
}


PooledIsolate::~PooledIsolate()
{
	try
	{
		_objectTemplates.clear();
		_pIsolate->Dispose();
	}
	catch (...)
	{
		poco_unexpected();
	}
	delete _pArrayBufferAllocator;
}


PooledIsolate* PooledIsolate::fromIsolate(v8::Isolate* pIsolate)
{
	void* pData = pIsolate->GetData(0);
	if (pData)
		return static_cast<PooledIsolate*>(pData);
	else
		return 0;
}


v8::Persistent<v8::ObjectTemplate>& PooledIsolate::objectTemplate(const std::string& name)
{
	return _objectTemplates[name].content();
}


std::size_t PooledIsolate::onNearHeapLimit(void* data, std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	v8::Isolate* pIsolate = reinterpret_cast<v8::Isolate*>(data);
	PooledIsolate* pSelf = fromIsolate(pIsolate);

	if (currentHeapLimit <= pSelf->_memoryLimit)
	{
		JSExecutor::Ptr pExecutor = JSExecutor::current();
		if (pExecutor)
		{
			pExecutor->handleMemoryWarning(pSelf->_memoryLimit*2, pSelf->_memoryLimit);
		}
		return pSelf->_memoryLimit*2;
	}
	else
	{
		JSExecutor::Ptr pExecutor = JSExecutor::current();
		if (pExecutor)
		{
			pExecutor->handleOutOfMemory(currentHeapLimit, pSelf->_memoryLimit);
		}
		return pSelf->_memoryLimit + pSelf->_memoryLimit/2;
	}
}


} } } // namespace Poco::JS::Core
