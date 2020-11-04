//
// JSServletExecutor.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JSServletExecutor.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/StreamCopier.h"
#include "v8.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


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


JSServletExecutor::JSServletExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& script, const Poco::URI& scriptURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit):
	JSExecutor(pContext, pBundle, script, scriptURI, moduleSearchPaths, memoryLimit)
{
}


void JSServletExecutor::prepareRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	_pResponse = &response;

	_pRequestHolder = new Poco::JS::Net::RequestRefHolderImpl<Poco::Net::HTTPServerRequest>(request);
	_pResponseHolder = new Poco::JS::Net::ResponseRefHolderImpl<Poco::Net::HTTPServerResponse>(response);
	_pForm = new Poco::Net::HTMLForm(request, request.stream());
	_pSessionHolder = 0;

	Poco::OSP::Web::WebSession::Ptr pSession;
	std::string sessionId = context()->thisBundle()->properties().getString("websession.id", "");
	if (!sessionId.empty())
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(sessionId, request);
			if (pSession)
			{
				_pSessionHolder = new SessionHolder(context(), pSession);
			}
		}
	}
}


void JSServletExecutor::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::StreamCopier::copyToString(request.stream(), _pRequestHolder->content());

	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	v8::Local<v8::Object> global = context->Global();

	v8::Local<v8::Function> servletFunction = v8::Local<v8::Function>::Cast(global->Get(v8::String::NewFromUtf8(pIsolate, "$servlet")));

	Poco::JS::Net::HTTPRequestWrapper httpRequestWrapper;
	Poco::JS::Net::HTTPResponseWrapper httpResponseWrapper;
	Poco::JS::Net::HTMLFormWrapper formWrapper;
	SessionWrapper sessionWrapper;

	v8::Handle<v8::Value> argv[4];
	argv[0] = httpRequestWrapper.wrapNative(pIsolate, &*_pRequestHolder);
	argv[1] = httpResponseWrapper.wrapNative(pIsolate, &*_pResponseHolder);
	argv[2] = formWrapper.wrapNative(pIsolate, &*_pForm);

	if (_pSessionHolder)
	{
		argv[3] = sessionWrapper.wrapNative(pIsolate, &*_pSessionHolder);
	}
	else
	{
		argv[3] = v8::Null(pIsolate);
	}

	v8::Local<v8::Value> receiver = global;
	callInContext(servletFunction, receiver, 4, argv);
}


void JSServletExecutor::handleError(const ErrorInfo& errorInfo)
{
	JSExecutor::handleError(errorInfo);
	if (_pResponse && !_pResponse->sent())
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


} } } } // namespace Poco::OSP::JS::Web
