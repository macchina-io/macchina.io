//
// JSServletExecutor.cpp
//
// $Id: //poco/1.4/OSP/JS/src/JSServletExecutor.cpp#2 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "JSServletExecutor.h"
#include "Poco/JS/Net/HTMLFormWrapper.h"
#include "Poco/StreamCopier.h"
#include "v8.h"
#include <iostream>


namespace Poco {
namespace OSP {
namespace JS {


namespace
{
	std::string htmlize(const std::string& str)
	{
		std::string::const_iterator it(str.begin());
		std::string::const_iterator end(str.end());
		std::string html;
		for (; it != end; ++it)
		{
			switch (*it)
			{
			case '<': html += "&lt;"; break;
			case '>': html += "&gt;"; break;
			case '"': html += "&quot;"; break;
			case '&': html += "&amp;"; break;
			default:  html += *it; break;
			}
		}
		return html;
	}
}


JSServletExecutor::JSServletExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& script, const Poco::URI& scriptURI, Poco::UInt64 memoryLimit, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response):
	JSExecutor(pContext, pBundle, script, scriptURI, memoryLimit),
	_pRequest(&request),
	_pResponse(&response),
	_pForm(new Poco::Net::HTMLForm(request, request.stream()))
{
}


void JSServletExecutor::reset(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	_pRequest = &request;
	_pResponse = &response;
	_pForm = new Poco::Net::HTMLForm(request, request.stream());
}


void JSServletExecutor::run()
{
	_pRequestHolder = new Poco::JS::Net::RequestRefHolderImpl<Poco::Net::HTTPServerRequest>(*_pRequest);
	_pResponseHolder = new Poco::JS::Net::ResponseRefHolderImpl<Poco::Net::HTTPServerResponse>(*_pResponse);
	JSExecutor::run();
	_pRequestHolder = 0;
	_pResponseHolder = 0;
}


void JSServletExecutor::scriptCompleted()
{
	while (!v8::V8::IdleNotification()) {}
}


void JSServletExecutor::registerGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	JSExecutor::registerGlobals(global, pIsolate);
	updateGlobals(global, pIsolate);
}


void JSServletExecutor::updateGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	JSExecutor::updateGlobals(global, pIsolate);

	v8::HandleScope handleScope(pIsolate);

	Poco::JS::Net::HTTPRequestWrapper httpRequestWrapper;
	v8::Local<v8::Object> requestObject = httpRequestWrapper.wrapNative(pIsolate, &*_pRequestHolder);
	global->Set(v8::String::NewFromUtf8(pIsolate, "request"), requestObject);

	Poco::JS::Net::HTTPResponseWrapper httpResponseWrapper;
	v8::Local<v8::Object> responseObject = httpResponseWrapper.wrapNative(pIsolate, &*_pResponseHolder);
	global->Set(v8::String::NewFromUtf8(pIsolate, "response"), responseObject);

	Poco::JS::Net::HTMLFormWrapper formWrapper;
	v8::Local<v8::Object> formObject = formWrapper.wrapNative(pIsolate, &*_pForm);
	global->Set(v8::String::NewFromUtf8(pIsolate, "form"), formObject);
	
	Poco::StreamCopier::copyToString(_pRequest->stream(), _pRequestHolder->content());
}


void JSServletExecutor::handleError(const ErrorInfo& errorInfo)
{
	JSExecutor::handleError(errorInfo);
	if (!_pResponse->sent())
	{
		_pResponse->setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
		_pResponse->setChunkedTransferEncoding(false);
		_pResponse->setContentType("text/html");
		_pResponse->send()
			<< "<html>"
			<< "<head><title>" << _pResponse->getStatus() << ": " << _pResponse->getReason() << "</title></head>"
			<< "<body>"
			<< "<h1>" << _pResponse->getStatus() << ": " << _pResponse->getReason() << "</h1>"
			<< "<p>" << htmlize(errorInfo.message) << "</p>"
			<< "</body>"
			<< "</html>";
	}
}


} } } // namespace Poco::OSP::JS
