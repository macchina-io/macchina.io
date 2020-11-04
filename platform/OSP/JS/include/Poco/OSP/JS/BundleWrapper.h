//
// BundleWrapper.h
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_BundleWrapper_INCLUDED
#define OSP_JS_BundleWrapper_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API BundleWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OSP::Bundle.
{
public:
	BundleWrapper();
		/// Creates the BundleWrapper.

	~BundleWrapper();
		/// Destroys the BundleWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void symbolicName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void version(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void path(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void state(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void active(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getResourceString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getResourceBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getLocalizedResourceString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getLocalizedResourceBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_BundleWrapper_INCLUDED
