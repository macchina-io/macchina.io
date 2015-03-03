//
// JSServletExecutor.h
//
// $Id: //poco/1.4/OSP/JS/src/JSServletExecutor.h#2 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_ServletExecutor_INCLUDED
#define OSP_JS_ServletExecutor_INCLUDED


#include "JSExecutor.h"
#include "SessionWrapper.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/SharedPtr.h"	


namespace Poco {
namespace OSP {
namespace JS {


class JSServletExecutor: public JSExecutor
	/// This class executes JavaScript code for servlets and JavaScript server pages.
	///
	/// Adds the following global JavaScript objects:
	///   - request (Poco::Net::HTTPServerRequest wrapper)
	///   - response (Poco::Net::HTTPServerResponse wrapper)
	///   - form (Poco::Net::HTMLForm wrapper)
{
public:
	typedef Poco::AutoPtr<JSServletExecutor> Ptr;

	JSServletExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& script, const Poco::URI& scriptURI, Poco::UInt64 memoryLimit, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Creates the ServletExecutor.

	void reset(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Resets the ServletExecutor and sets new request and response objects.

	// JSExecutor
	void run();
		
protected:
	void registerGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	void updateGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	void handleError(const ErrorInfo& errorInfo);
	void scriptCompleted();

private:
	Poco::Net::HTTPServerRequest* _pRequest;
	Poco::Net::HTTPServerResponse* _pResponse;
	Poco::SharedPtr<Poco::JS::Net::RequestHolder> _pRequestHolder;
	Poco::SharedPtr<Poco::JS::Net::ResponseHolder> _pResponseHolder;
	Poco::SharedPtr<SessionHolder> _pSessionHolder;
	Poco::SharedPtr<Poco::Net::HTMLForm> _pForm;
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_ServletExecutor_INCLUDED
