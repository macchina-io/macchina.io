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
#include "Poco/OSP/Bundle.h"


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
	static void vendor(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void copyright(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void path(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void runLevel(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void state(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void active(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void lazyStart(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void sealed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void preventUninstall(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void requiredBundles(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void requiredModules(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void providedModules(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getResourceString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getResourceBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getLocalizedResourceString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getLocalizedResourceBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void equals(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toJSON(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
	static v8::Local<v8::Array> dependencies(v8::Isolate* pIsolate, const Poco::OSP::Bundle::Dependencies& deps);
	static v8::Local<v8::Array> modules(v8::Isolate* pIsolate, const Poco::OSP::Bundle::Modules& mods);
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_BundleWrapper_INCLUDED
