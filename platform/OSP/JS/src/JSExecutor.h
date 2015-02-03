//
// JSExecutor.h
//
// $Id: //poco/1.4/OSP/JS/src/JSExecutor.h#8 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_JSExecutor_INCLUDED
#define OSP_JS_JSExecutor_INCLUDED


#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "v8.h"


namespace Poco {
namespace OSP {
namespace JS {


class JSExecutor: public Poco::JS::Core::JSExecutor
	/// An extension of the Poco::JS::Core::JSExecutor for executing JavaScript
	/// code within an OSP environment.
	///
	/// Adds the following global JavaScript objects:
	///   - bundle (Poco::OSP::Bundle wrapper)
	///   - properties (bundle properties wrapper)
	///   - serviceRegistry (Poco::OSP::ServiceRegistry wrapper)
	///   - logger (bundle context logger wrapper)
	///   - HTTPRequest (HTTP request constructor)
	///   - DBSession (Database session constructor)
{
public:
	typedef Poco::AutoPtr<JSExecutor> Ptr;

	JSExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& source, const Poco::URI& sourceURI, Poco::UInt64 memoryLimit);
		/// Creates the JSExecutor.

	~JSExecutor();
		/// Destroys the JSExecutor.
	
protected:
	void registerGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	void handleError(const ErrorInfo& errorInfo);

private:	
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::Bundle::Ptr _pBundle;
};


class TimedJSExecutor: public Poco::JS::Core::TimedJSExecutor
	/// An extension of the Poco::JS::Core::TimedJSExecutor for executing JavaScript
	/// code within an OSP environment.
	///
	/// Will stop the executing JavaScript when the containing bundle
	/// is stopped.
	///
	/// Adds the following global JavaScript objects:
	///   - bundle (Poco::OSP::Bundle wrapper)
	///   - properties (bundle properties wrapper)
	///   - serviceRegistry (Poco::OSP::ServiceRegistry wrapper)
	///   - logger (bundle context logger wrapper)
	///   - HTTPRequest (HTTP request constructor)
	///   - DBSession (Database session constructor)
{
public:
	typedef Poco::AutoPtr<TimedJSExecutor> Ptr;

	TimedJSExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& source, const Poco::URI& sourceURI, Poco::UInt64 memoryLimit);
		/// Creates the TimedJSExecutor.
		
	~TimedJSExecutor();
		/// Destroys the TimedJSExecutor.

protected:
	void registerGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	void handleError(const ErrorInfo& errorInfo);
	void onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev);

private:	
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::Bundle::Ptr _pBundle;
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_JSExecutor_INCLUDED
