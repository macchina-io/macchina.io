//
// BundleContextWrapper.cpp
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/BundleContextWrapper.h"
#include "Poco/OSP/JS/BundleWrapper.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/SharedPtr.h"
#include <memory>


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {


BundleContextWrapper::BundleContextWrapper()
{
}


BundleContextWrapper::~BundleContextWrapper()
{
}


v8::Handle<v8::ObjectTemplate> BundleContextWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
	objectTemplate->SetInternalFieldCount(1);
	objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "thisBundle"s), thisBundle);
	objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "findBundle"s), v8::FunctionTemplate::New(pIsolate, findBundle));
	objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "listBundles"s), v8::FunctionTemplate::New(pIsolate, listBundles));
	return handleScope.Escape(objectTemplate);
}


void BundleContextWrapper::thisBundle(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::OSP::BundleContext* pBundleContext = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::BundleContext>(info);
	try
	{
		Poco::OSP::Bundle::Ptr pBundle = pBundleContext->thisBundle();
		BundleWrapper bundleWrapper;
		v8::Persistent<v8::Object>& bundleObject(bundleWrapper.wrapNativePersistent(pIsolate, pBundle));
		info.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bundleObject));
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void BundleContextWrapper::findBundle(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::OSP::BundleContext* pBundleContext = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::BundleContext>(args);
	try
	{
		Poco::OSP::Bundle::Ptr pBundle;
		if (args[0]->IsNumber())
		{
			pBundle = pBundleContext->findBundle(args[0]->Int32Value(context).FromMaybe(-1));
		}
		else
		{
			pBundle = pBundleContext->findBundle(toString(pIsolate, args[0]));
		}
		if (pBundle)
		{
			BundleWrapper bundleWrapper;
			v8::Persistent<v8::Object>& bundleObject(bundleWrapper.wrapNativePersistent(pIsolate, pBundle));
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bundleObject));
		}
		else
		{
			args.GetReturnValue().Set(v8::Null(pIsolate));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BundleContextWrapper::listBundles(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::OSP::BundleContext* pBundleContext = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::BundleContext>(args);
	try
	{
		std::vector<Poco::OSP::Bundle::Ptr> bundles;
		pBundleContext->listBundles(bundles);

		v8::Local<v8::Array> bundlesArray = v8::Array::New(pIsolate, static_cast<int>(bundles.size()));
		if (!bundlesArray.IsEmpty())
		{
			for (unsigned i = 0; i < static_cast<unsigned>(bundles.size()); i++)
			{
				BundleWrapper bundleWrapper;
				v8::Persistent<v8::Object>& bundleObject(bundleWrapper.wrapNativePersistent(pIsolate, bundles[i]));
				V8_CHECK_SET_RESULT(bundlesArray->Set(context, i, v8::Local<v8::Object>::New(pIsolate, bundleObject)));
			}
		}
		args.GetReturnValue().Set(bundlesArray);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::OSP::JS
