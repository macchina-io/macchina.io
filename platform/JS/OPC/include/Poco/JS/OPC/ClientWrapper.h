//
// ClientWrapper.h
//
// $Id: //poco/1.4/JS/OPC/include/Poco/JS/OPC/ClientWrapper.h#6 $
//
// Library: JS/OPC
// Package: Wrappers
// Module:  ClientWrapper
//
// Definition of the ClientWrapper class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_OPC_ClientWrapper_INCLUDED
#define JS_OPC_ClientWrapper_INCLUDED


#include "Poco/JS/OPC/OPC.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/OPC/Client.h"


namespace Poco {
namespace JS {
namespace OPC {


class JSOPC_API ClientHolder
{
public:
	ClientHolder(const std::string& server,
		int port = 16664,
		const std::string& user = "",
		const std::string& pass = "",
		bool doConnect = true,
		const std::string& proto = "opc.tcp");
		/// Creates the ClientHolder.
		
	~ClientHolder();
		/// Destroys the ClientHolder.

	Poco::OPC::Client& client()
	{
		return _client;
	}

private:
	Poco::OPC::Client _client;
};


class JSOPC_API ClientWrapper: public JS::Core::Wrapper
	/// JavaScript wrapper for Poco::OPC::Client.
{
public:
	ClientWrapper();
		/// Creates the ClientWrapper.

	~ClientWrapper();
		/// Destroys the ClientWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Creates a JavaScript Client object.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void serverDateTime(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void read(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::OPC


#endif // JS_OPC_ClientWrapper_INCLUDED
