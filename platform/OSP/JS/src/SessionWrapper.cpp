//
// SessionWrapper.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SessionWrapper.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"


namespace Poco {
namespace OSP {
namespace JS {


SessionWrapper::SessionWrapper()
{
}


SessionWrapper::~SessionWrapper()
{
}


v8::Handle<v8::ObjectTemplate> SessionWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> bundleTemplate = v8::ObjectTemplate::New();
	bundleTemplate->SetInternalFieldCount(1);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "id"), id);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "username"), username);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "authenticated"), authenticated);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "csrfToken"), csrfToken);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "clientAddress"), clientAddress);
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setInt"), v8::FunctionTemplate::New(pIsolate, setInt));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getInt"), v8::FunctionTemplate::New(pIsolate, getInt));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setString"), v8::FunctionTemplate::New(pIsolate, setString));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getString"), v8::FunctionTemplate::New(pIsolate, getString));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "erase"), v8::FunctionTemplate::New(pIsolate, erase));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "authorize"), v8::FunctionTemplate::New(pIsolate, authorize));
	return handleScope.Escape(bundleTemplate);
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


} } } // namespace Poco::OSP::JS
