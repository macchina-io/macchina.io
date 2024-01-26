//
// SessionWrapper.h
//
// Copyright (c) 2015-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_Web_SessionWrapper_INCLUDED
#define OSP_JS_Web_SessionWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/OSP/Web/WebSession.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class SessionHolder
{
public:
	SessionHolder(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Web::WebSession::Ptr pSession):
		_pContext(pContext),
		_pSession(pSession)
	{
	}
	
	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}
	
	Poco::OSP::Web::WebSession::Ptr session() const
	{
		return _pSession;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::Web::WebSession::Ptr _pSession;
};


class SessionWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OSP::Web::WebSession.
{
public:
	SessionWrapper();
		/// Creates the SessionWrapper.
	
	~SessionWrapper();
		/// Destroys the SessionWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void id(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void username(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void authenticated(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void csrfToken(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void clientAddress(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setInt(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getInt(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setBool(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getBool(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void erase(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void authorize(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_Web_SessionWrapper_INCLUDED
