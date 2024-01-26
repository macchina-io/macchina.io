//
// TimerWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  TimerWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/TimerWrapper.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/JS/Core/PooledIsolate.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


TimerWrapper::TimerWrapper()
{
}


TimerWrapper::~TimerWrapper()
{
}


v8::Handle<v8::ObjectTemplate> TimerWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.Timer"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "cancelled"s), cancelled);
		objectTemplate->Set(toV8Internalized(pIsolate, "cancel"s), v8::FunctionTemplate::New(pIsolate, cancel));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> timerTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(timerTemplate);
}


void TimerWrapper::cancel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::Util::TimerTask* pTimerTask = Poco::JS::Core::Wrapper::unwrapNative<Poco::Util::TimerTask>(args);
	try
	{
		pTimerTask->cancel();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void TimerWrapper::cancelled(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::Util::TimerTask* pTimerTask = Poco::JS::Core::Wrapper::unwrapNative<Poco::Util::TimerTask>(info);
	info.GetReturnValue().Set(pTimerTask->isCancelled());
}


} } } // namespace Poco::JS::Core
