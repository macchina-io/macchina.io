//
// DataModule.cpp
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/Module.h"
#include "Poco/OSP/JS/ModuleFactory.h"
#include "Poco/JS/Data/SessionWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/ClassLibrary.h"
#include "v8.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Data {


class DataWrapper: public Poco::JS::Core::Wrapper
{
public:
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate)
	{
		v8::EscapableHandleScope handleScope(pIsolate);
		Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
		poco_check_ptr (pPooledIso);
		v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OSP.Data"));
		if (pooledObjectTemplate.IsEmpty())
		{
			v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
			objectTemplate->SetInternalFieldCount(1);

			objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "Session"), v8::FunctionTemplate::New(pIsolate, Poco::JS::Data::SessionWrapper::construct));

			pooledObjectTemplate.Reset(pIsolate, objectTemplate);
		}
		v8::Local<v8::ObjectTemplate> dataTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
		return handleScope.Escape(dataTemplate);
	}
};


class DataModule: public Poco::JS::Core::Module
{
public:
	v8::Local<v8::Object> exportIt(v8::Isolate* pIsolate)
	{
		v8::EscapableHandleScope handleScope(pIsolate);

		DataWrapper dataWrapper;
		v8::Local<v8::Object> moduleObject = dataWrapper.wrapNative(pIsolate);

		return handleScope.Escape(moduleObject);
	}
};


class DataModuleFactory: public Poco::OSP::JS::ModuleFactory
{
public:
	Poco::JS::Core::Module* createModule()
	{
		return new DataModule;
	}
};


} } } } // namespace Poco::OSP::JS::Data


POCO_BEGIN_NAMED_MANIFEST(Module, Poco::OSP::JS::ModuleFactory)
	POCO_EXPORT_CLASS(Poco::OSP::JS::Data::DataModuleFactory)
POCO_END_MANIFEST

