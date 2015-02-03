//
// ServiceRefWrapper.h
//
// $Id: //poco/1.4/OSP/JS/src/ServiceRefWrapper.h#3 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_ServiceRefWrapper_INCLUDED
#define OSP_JS_ServiceRefWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/OSP/ServiceRef.h"


namespace Poco {
namespace OSP {
namespace JS {


class ServiceRefWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OSP::ServiceRef.
{
public:
	ServiceRefWrapper();
		/// Creates the ServiceRefWrapper.
	
	~ServiceRefWrapper();
		/// Destroys the ServiceRefWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void instance(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getProperty(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	
	friend class ServiceRegistryWrapper;
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_ServiceRefWrapper_INCLUDED
