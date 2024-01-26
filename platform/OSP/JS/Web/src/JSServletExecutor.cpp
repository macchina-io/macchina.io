//
// JSServletExecutor.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JSServletExecutor.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/StreamCopier.h"
#include "Poco/FileStream.h"
#include "Poco/NullStream.h"
#include "Poco/Logger.h"
#include "Poco/Format.h"
#include "Poco/Buffer.h"
#include "v8.h"


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class UploadsPartHandler: public Poco::Net::PartHandler
{
public:
	UploadsPartHandler(std::vector<JSServletExecutor::UploadInfo::Ptr>& uploads, const std::string& uri, std::streamsize maxUploadSize, unsigned maxUploadCount):
		_uploads(uploads),
		_uri(uri),
		_maxUploadSize(maxUploadSize),
		_maxUploadCount(maxUploadCount)
	{
	}

	void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
	{
		_uploadCount++;
		try
		{
			JSServletExecutor::UploadInfo::Ptr pUpload = new JSServletExecutor::UploadInfo;
			pUpload->header = header;
			pUpload->contentType = header.get("Content-Type"s, ""s);

			const std::string contentDisposition = header.get("Content-Disposition"s, ""s);
			if (!contentDisposition.empty())
			{
				std::string disp;
				Poco::Net::NameValueCollection params;
				Poco::Net::MessageHeader::splitParameters(contentDisposition, disp, params);
				pUpload->name = params.get("name"s, ""s);
				pUpload->filename = params.get("filename"s, ""s);
			}

			if (_uploadCount <= _maxUploadCount)
			{
				Poco::FileOutputStream fileStream(pUpload->file.path());
				pUpload->size = copyStream(stream, fileStream, _maxUploadSize);
				fileStream.close();
				if (pUpload->size < _maxUploadSize)
				{
					_uploads.push_back(pUpload);
				}
				else
				{
					Poco::NullOutputStream nullStream;
					pUpload->size += Poco::StreamCopier::copyStream(stream, nullStream);
					_logger.warning("File \"%s\" (%s) uploaded via page \"%s\", with a size of %?d bytes, exceeds maximum upload size of %?d bytes and has been discarded."s, pUpload->filename, pUpload->name, _uri, pUpload->size, _maxUploadSize);
					pUpload->file.remove();
				}
			}
			else
			{
				Poco::NullOutputStream nullStream;
				Poco::StreamCopier::copyStream(stream, nullStream);
				_logger.warning("File \"%s\" (%s) uploaded via page \"%s\" exceeds maximum upload count %u and has been discarded."s, pUpload->filename, pUpload->name, _uri, _maxUploadCount);
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Failed to process uploaded file via page \"%s\": %s"s, _uri, exc.displayText());
		}
	}

protected:
	std::streamsize copyStream(std::istream& istr, std::ostream& ostr, std::streamsize maxFileSize)
	{
		const std::size_t bufferSize = 8192;

		Poco::Buffer<char> buffer(bufferSize);
		std::streamsize len = 0;
		istr.read(buffer.begin(), bufferSize);
		std::streamsize n = istr.gcount();
		while (n > 0 && len < maxFileSize)
		{
			len += n;
			ostr.write(buffer.begin(), n);
			if (istr && ostr)
			{
				istr.read(buffer.begin(), bufferSize);
				n = istr.gcount();
			}
			else n = 0;
		}
		return len + n;
	}

private:
	std::vector<JSServletExecutor::UploadInfo::Ptr>& _uploads;
	const std::string& _uri;
	std::streamsize _maxUploadSize;
	unsigned _maxUploadCount;
	unsigned _uploadCount = 0;
	Poco::Logger& _logger = Poco::Logger::get("JSServletExecutor.UploadsPartHandler"s);
};


JSServletExecutor::JSServletExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& script, const Poco::URI& scriptURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit, Poco::UInt64 maxUploadSize, unsigned maxUploadCount):
	JSExecutor(pContext, pBundle, script, scriptURI, moduleSearchPaths, memoryLimit),
	_maxUploadSize(maxUploadSize),
	_maxUploadCount(maxUploadCount)
{
}


void JSServletExecutor::prepareRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	_pResponse = &response;

	_pRequestHolder = new Poco::JS::Net::RequestRefHolderImpl<Poco::Net::HTTPServerRequest>(request);
	_pResponseHolder = new Poco::JS::Net::ResponseRefHolderImpl<Poco::Net::HTTPServerResponse>(response);
	_uploads.clear();
	UploadsPartHandler uploadsPartHandler(_uploads, request.getURI(), _maxUploadSize, _maxUploadCount);
	_pForm = new Poco::Net::HTMLForm(request, request.stream(), uploadsPartHandler);
	_pSessionHolder = 0;

	Poco::OSP::Web::WebSession::Ptr pSession;
	std::string sessionId = context()->thisBundle()->properties().getString("websession.id"s, ""s);
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

	v8::MaybeLocal<v8::Value> maybeServletValue = global->Get(context, Wrapper::toV8Internalized(pIsolate, "$servlet"s));
	v8::Local<v8::Value> servletValue;
	if (maybeServletValue.ToLocal(&servletValue) && servletValue->IsFunction())
	{
		v8::Local<v8::Function> servletFunction = v8::Local<v8::Function>::Cast(servletValue);

		Poco::JS::Net::HTTPRequestWrapper httpRequestWrapper;
		Poco::JS::Net::HTTPResponseWrapper httpResponseWrapper;
		Poco::JS::Net::HTMLFormWrapper formWrapper;
		SessionWrapper sessionWrapper;

		v8::Handle<v8::Value> argv[5];
		argv[0] = httpRequestWrapper.wrapNative(pIsolate, &*_pRequestHolder).ToLocalChecked();
		argv[1] = httpResponseWrapper.wrapNative(pIsolate, &*_pResponseHolder).ToLocalChecked();
		argv[2] = formWrapper.wrapNative(pIsolate, &*_pForm).ToLocalChecked();
		
		v8::Local<v8::Array> uploads = v8::Array::New(pIsolate, static_cast<int>(_uploads.size()));
		for (int i = 0; i < static_cast<int>(_uploads.size()); i++)
		{
			v8::Local<v8::Object> upload = v8::Object::New(pIsolate);
			V8_CHECK_SET_RESULT(upload->Set(context, Wrapper::toV8Internalized(pIsolate, "path"s), Wrapper::toV8String(pIsolate, _uploads[i]->file.path())));	
			V8_CHECK_SET_RESULT(upload->Set(context, Wrapper::toV8Internalized(pIsolate, "name"s), Wrapper::toV8String(pIsolate, _uploads[i]->name)));	
			V8_CHECK_SET_RESULT(upload->Set(context, Wrapper::toV8Internalized(pIsolate, "filename"s), Wrapper::toV8String(pIsolate, _uploads[i]->filename)));	
			V8_CHECK_SET_RESULT(upload->Set(context, Wrapper::toV8Internalized(pIsolate, "contentType"s), Wrapper::toV8String(pIsolate, _uploads[i]->contentType)));	
			V8_CHECK_SET_RESULT(upload->Set(context, Wrapper::toV8Internalized(pIsolate, "size"s), v8::Number::New(pIsolate, static_cast<double>(_uploads[i]->size))));
			v8::Local<v8::Object> header = v8::Object::New(pIsolate);
			for (const auto& h: _uploads[i]->header)
			{
				V8_CHECK_SET_RESULT(header->Set(context, Wrapper::toV8String(pIsolate, h.first), Wrapper::toV8String(pIsolate, h.second)));
			}
			V8_CHECK_SET_RESULT(upload->Set(context, Wrapper::toV8Internalized(pIsolate, "headers"s), header));
			V8_CHECK_SET_RESULT(uploads->Set(context, i, upload));
		}
		argv[3] = uploads;

		if (_pSessionHolder)
		{
			argv[4] = sessionWrapper.wrapNative(pIsolate, &*_pSessionHolder).ToLocalChecked();
		}
		else
		{
			argv[4] = v8::Null(pIsolate);
		}

		v8::Local<v8::Value> receiver = global;
		callInContext(pIsolate, context, servletFunction, receiver, 5, argv);
		_uploads.clear();
	}
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
			<< "<p>" << Poco::Net::htmlize(errorInfo.message) << "</p>"
			<< "</body>"
			<< "</html>";
	}
}


} } } } // namespace Poco::OSP::JS::Web
