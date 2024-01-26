//
// BundleContextWrapper.h
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_BundleContextWrapper_INCLUDED
#define OSP_JS_BundleContextWrapper_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API BundleContextWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OSP::Bundle.
{
public:
	BundleContextWrapper();
		/// Creates the BundleContextWrapper.

	~BundleContextWrapper();
		/// Destroys the BundleContextWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void thisBundle(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void findBundle(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void listBundles(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_BundleContextWrapper_INCLUDED
