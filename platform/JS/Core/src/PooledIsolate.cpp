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
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Exception.h"


namespace Poco {
namespace JS {
namespace Core {


PooledIsolate::PooledIsolate():
	_pIsolate(v8::Isolate::New())
{
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
