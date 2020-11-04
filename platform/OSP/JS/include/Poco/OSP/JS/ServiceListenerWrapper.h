//
// ServiceListenerWrapper.h
//
// Copyright (c) 2013-2018, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_ServiceListenerWrapper_INCLUDED
#define OSP_JS_ServiceListenerWrapper_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/OSP/ServiceListener.h"
#include "v8.h"


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API ServiceListenerHolder: public Poco::RefCountedObject
{
public:
	using Ptr = Poco::AutoPtr<ServiceListenerHolder>;

	ServiceListenerHolder(
		v8::Isolate* pIsolate,
		Poco::JS::Core::JSExecutor::Ptr pExecutor,
		Poco::OSP::ServiceRegistry& registry,
		const std::string& query,
		v8::Local<v8::Function> registeredCallback,
		v8::Local<v8::Function> unregisteredCallback);

	~ServiceListenerHolder();

	void dispose();

protected:
	void onServiceRegistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef);
	void onServiceUnregistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef);

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::JSExecutor::Ptr _pExecutor;
	v8::Persistent<v8::Function> _registeredCallback;
	v8::Persistent<v8::Function> _unregisteredCallback;
	Poco::OSP::ServiceListener::Ptr _pListener;
};


class OSPJS_API ServiceListenerWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OSP::ServiceRef.
{
public:
	ServiceListenerWrapper();
		/// Creates the ServiceListenerWrapper.

	~ServiceListenerWrapper();
		/// Destroys the ServiceListenerWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void dispose(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_ServiceListenerWrapper_INCLUDED
