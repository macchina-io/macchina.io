//
// PooledIsolate.cpp
//
// $Id: //poco/1.4/JS/Core/src/PooledIsolate.cpp#5 $
//
// Library: JSCore
// Package: JSCore
// Module:  IsolatePool
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/JSException.h"
#include <cstdlib>


namespace Poco {
namespace JS {
namespace Core {


class ArrayBufferAllocator: public v8::ArrayBuffer::Allocator
{
public:
	void* Allocate(size_t length)
	{
		return std::calloc(length, 1);
	}

	void* AllocateUninitialized(size_t length)
	{
		return std::malloc(length);
	}
 
	void Free(void* data, size_t length)
	{
		std::free(data);
	}
};


PooledIsolate::PooledIsolate(Poco::UInt64 memoryLimit):
	_pIsolate(0)
{
	static ArrayBufferAllocator arrayBufferAllocator;

	v8::Isolate::CreateParams params;
	params.constraints.ConfigureDefaults(memoryLimit, memoryLimit);
	params.array_buffer_allocator = &arrayBufferAllocator;
	_pIsolate = v8::Isolate::New(params);
	if (!_pIsolate) throw JSException("Cannot create isolate");
	_pIsolate->SetData(0, this);
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


} } } // namespace Poco::JS::Core
