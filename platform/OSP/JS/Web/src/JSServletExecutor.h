//
// JSServletExecutor.h
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_ServletExecutor_INCLUDED
#define OSP_JS_ServletExecutor_INCLUDED


#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Net/HTMLFormWrapper.h"
#include "SessionWrapper.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/SharedPtr.h"	


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSServletExecutor: public JSExecutor
	/// This class executes JavaScript code for servlets and JavaScript server pages.
	///
	/// Provides the following JavaScript objects as servlet parameters:
	///   - request (Poco::Net::HTTPServerRequest wrapper)
	///   - response (Poco::Net::HTTPServerResponse wrapper)
	///   - form (Poco::Net::HTMLForm wrapper)
	///   - session (Poco::OSP::Web::WebSession wrapper)
{
public:
	typedef Poco::AutoPtr<JSServletExecutor> Ptr;

	JSServletExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& script, const Poco::URI& scriptURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit);
		/// Creates the ServletExecutor.

	void prepareRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Prepares the request.

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Handles the request by invoking the $servlet() function.
		
protected:
	void handleError(const ErrorInfo& errorInfo);
	
private:
	Poco::Net::HTTPServerResponse* _pResponse;
	Poco::SharedPtr<Poco::JS::Net::RequestHolder> _pRequestHolder;
	Poco::SharedPtr<Poco::JS::Net::ResponseHolder> _pResponseHolder;
	Poco::SharedPtr<Poco::Net::HTMLForm> _pForm;
	Poco::SharedPtr<SessionHolder> _pSessionHolder;
};


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_ServletExecutor_INCLUDED
