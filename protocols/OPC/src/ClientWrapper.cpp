//
// ClientWrapper.cpp
//
// $Id: //poco/1.4/IoT/OPC/src/ClientWrapper.cpp#6 $
//
// Library: OPC
// Package: Wrappers
// Module:  ClientWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/OPC/ClientWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Types.h"
#include "Poco/Format.h"


namespace IoT {
namespace OPC {


ClientHolder::ClientHolder(const std::string& server,
		int port,
		const std::string& user,
		const std::string& pass,
		bool doConnect,
		const std::string& proto): _client(server, port, user, pass, doConnect, proto)
{
}


ClientHolder::~ClientHolder()
{
}


ClientWrapper::ClientWrapper()
{
}


ClientWrapper::~ClientWrapper()
{
}


v8::Handle<v8::FunctionTemplate> ClientWrapper::constructor(v8::Isolate* pIsolate)
{
	return v8::FunctionTemplate::New(pIsolate, construct);
}


v8::Handle<v8::ObjectTemplate> ClientWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OPC.Client"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New();
		objectTemplate->SetInternalFieldCount(1);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "serverDateTime"), v8::FunctionTemplate::New(pIsolate, serverDateTime));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "read"), v8::FunctionTemplate::New(pIsolate, read));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> dateTimeTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(dateTimeTemplate);
}


void ClientWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string server;
	int port = OPC_STANDARD_PORT;
	std::string user;
	std::string pass;
	bool doConnect = true;
	std::string proto = "opc.tcp";

	if (args.Length() >= 1)
	{
		server = toString(args[0]);
		if (args.Length() >= 2)
		{
			if (args[1]->IsNumber())
			{
				port = args[1]->Int32Value();
			}
			else
			{
				returnException(args, std::string("bad argument: port must be number"));
				return;
			}
			if (args.Length() >= 3)
			{
				user = toString(args[2]);
				if (args.Length() >= 4)
				{
					pass = toString(args[3]);
					if (args.Length() >= 5)
					{
						doConnect = args[4]->BooleanValue();
						if (args.Length() >= 6) proto = toString(args[5]);
					}
				}
			}
		}
	}
	else
	{
		returnException(args, std::string("bad arguments: at least server address string required"));
		return;
	}

	ClientHolder* pClientHolder = 0;
	try
	{
		pClientHolder = new ClientHolder(server, port, user, pass, doConnect, proto);
		ClientWrapper wrapper;
		v8::Persistent<v8::Object>& clientObject(wrapper.wrapNativePersistent(args.GetIsolate(), pClientHolder));
		args.GetReturnValue().Set(clientObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pClientHolder;
		returnException(args, exc);
	}
}


void ClientWrapper::serverDateTime(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	ClientHolder* pClientHolder = Wrapper::unwrapNative<ClientHolder>(info);
	v8::Local<v8::String> ret = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), pClientHolder->client().readServerDateTimeStr().c_str());
	info.GetReturnValue().Set(ret);
}

void ClientWrapper::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		ClientHolder* pClientHolder = Wrapper::unwrapNative<ClientHolder>(args);
		if(pClientHolder)
		{
			if (args.Length() >= 2)
			{
				int nsIndex = 0;
				int idx = 0;
				if (args[idx]->IsNumber())
				{
					nsIndex = args[idx]->Int32Value();
				}
				else
				{
					returnException(args, Poco::format("invalid argument %d type (integer expected)", idx));
					return;
				}
				++idx;
				Poco::Dynamic::Var val;
				if (args[idx]->IsNumber())
				{
					int id = args[idx]->Int32Value();
					val = pClientHolder->client().read(nsIndex, id);
				}
				else if (args[idx]->IsString())
				{
					std::string name = toString(args[idx]);
					val = pClientHolder->client().read(nsIndex, name);
				}
				else
				{
					returnException(args, Poco::format("invalid argument %d type (integer or string expected)", idx));
					return;
				}

				const std::type_info& ti = val.type();
				if (ti == typeid(IoT::OPC::DateTime))
				{
					v8::Local<v8::String> ret = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),
						val.convert<IoT::OPC::DateTime>().toString().c_str());
					args.GetReturnValue().Set(ret); return;
				}
				else if (val.isNumeric())
				{
					if (val.isInteger())
					{
						v8::Local<v8::Integer> ret;
						if (val.isSigned())
						{
							ret = v8::Integer::New(v8::Isolate::GetCurrent(), val.convert<Poco::Int64>());
						}
						else
						{
							ret = v8::Integer::New(v8::Isolate::GetCurrent(), val.convert<Poco::UInt64>());
						}
						args.GetReturnValue().Set(ret); return;
					}
					else // floating point
					{
						v8::Local<v8::Number>ret = v8::Number::New(v8::Isolate::GetCurrent(), val.convert<double>());
						args.GetReturnValue().Set(ret); return;
					}
				}
				else if (val.isString())
				{
					v8::Local<v8::String> ret = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),
						val.convert<std::string>().c_str());
					args.GetReturnValue().Set(ret); return;
				}
				
			}
			else
			{
				returnException(args, Poco::format("invalid number of arguments (expected 2, received %d)", args.Length()));
				return;
			}
		}
		else
		{
			returnException(args, "OPC client is null"); return;
		}
	}
	catch(Poco::Exception& ex)
	{
		returnException(args, ex.displayText()); return;
	}
	catch(std::exception& ex)
	{
		returnException(args, ex.what()); return;
	}
}


} } // namespace IoT::OPC
