//
// SessionWrapper.cpp
//
// Copyright (c) 2015-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SessionWrapper.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/JS/Core/PooledIsolate.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


SessionWrapper::SessionWrapper()
{
}


SessionWrapper::~SessionWrapper()
{
}


v8::Handle<v8::ObjectTemplate> SessionWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledSessionTemplate(pPooledIso->objectTemplate("Web.Session"));
	if (pooledSessionTemplate.IsEmpty())
	{
		v8::Local<v8::ObjectTemplate> sessionTemplate = v8::ObjectTemplate::New(pIsolate);
		sessionTemplate->SetInternalFieldCount(1);
		sessionTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "id"), id);
		sessionTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "username"), username);
		sessionTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "authenticated"), authenticated);
		sessionTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "csrfToken"), csrfToken);
		sessionTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "clientAddress"), clientAddress);
		sessionTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setInt"), v8::FunctionTemplate::New(pIsolate, setInt));
		sessionTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getInt"), v8::FunctionTemplate::New(pIsolate, getInt));
		sessionTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setString"), v8::FunctionTemplate::New(pIsolate, setString));
		sessionTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getString"), v8::FunctionTemplate::New(pIsolate, getString));
		sessionTemplate->Set(v8::String::NewFromUtf8(pIsolate, "erase"), v8::FunctionTemplate::New(pIsolate, erase));
		sessionTemplate->Set(v8::String::NewFromUtf8(pIsolate, "authorize"), v8::FunctionTemplate::New(pIsolate, authorize));
		pooledSessionTemplate.Reset(pIsolate, sessionTemplate);
	}
	v8::Local<v8::ObjectTemplate> localSessionTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledSessionTemplate);
	return handleScope.Escape(localSessionTemplate);
}


void SessionWrapper::id(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(info);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	returnString(info, pSession->id());
}


void SessionWrapper::username(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(info);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	std::string username;
	if (pSession->has("username"))
	{
		try
		{
			username = pSession->getValue<std::string>("username");
		}
		catch (Poco::Exception&)
		{
		}
	}
	if (!username.empty())
	{
		returnString(info, username);
	}
}


void SessionWrapper::authenticated(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(info);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	std::string username;
	if (pSession->has("username"))
	{
		try
		{
			username = pSession->getValue<std::string>("username");
		}
		catch (Poco::Exception&)
		{
		}
	}
	info.GetReturnValue().Set(!username.empty());
}


void SessionWrapper::csrfToken(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(info);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	returnString(info, pSession->csrfToken());
}


void SessionWrapper::clientAddress(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(info);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	returnString(info, pSession->clientAddress().toString());
}


void SessionWrapper::getInt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;

	std::string name = toString(args[0]);
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(args);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	if (pSession->has(name))
	{
		try
		{
			int value = pSession->getValue<int>(name);
			args.GetReturnValue().Set(value);
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
	else
	{
		if (args.Length() > 1)
		{
			args.GetReturnValue().Set(args[1]);
		}
	}
}


void SessionWrapper::setInt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;

	std::string name = toString(args[0]);
	int value = args[1]->Int32Value();

	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(args);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();

	try
	{
		pSession->setValue(name, value);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SessionWrapper::getString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;

	std::string name = toString(args[0]);
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(args);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();
	if (pSession->has(name))
	{
		try
		{
			std::string value = pSession->getValue<std::string>(name);
			returnString(args, value);
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
	else
	{
		if (args.Length() > 1)
		{
			args.GetReturnValue().Set(args[1]);
		}
	}
}


void SessionWrapper::setString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;

	std::string name = toString(args[0]);
	std::string value = toString(args[1]);

	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(args);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();

	try
	{
		pSession->setValue(name, value);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SessionWrapper::erase(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;

	std::string name = toString(args[0]);

	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(args);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();

	try
	{
		pSession->erase(name);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SessionWrapper::authorize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;

	std::string permission = toString(args[0]);
	SessionHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<SessionHolder>(args);
	Poco::OSP::Web::WebSession::Ptr pSession = pHolder->session();

	bool authorized = false;
	try
	{
		std::string username = pSession->getValue<std::string>("username", "");
		if (!username.empty())
		{
			Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(pHolder->context(), "osp.auth");
			authorized = pAuthService->authorize(username, permission);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	args.GetReturnValue().Set(authorized);
}


} } } } // namespace Poco::OSP::JS::Web
