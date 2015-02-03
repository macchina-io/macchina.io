//
// ServiceRegistryWrapper.h
//
// $Id: //poco/1.4/OSP/JS/src/ServiceRegistryWrapper.h#2 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_ServiceRegistryWrapper_INCLUDED
#define OSP_JS_ServiceRegistryWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace OSP {
namespace JS {


class ServiceRegistryWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OSP::ServiceRegistry.
{
public:
	ServiceRegistryWrapper();
		/// Creates the ServiceRegistryWrapper.
	
	~ServiceRegistryWrapper();
		/// Destroys the ServiceRegistryWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void findByName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void find(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_ServiceRegistryWrapper_INCLUDED
