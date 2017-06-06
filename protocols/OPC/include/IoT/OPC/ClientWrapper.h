//
// ClientWrapper.h
//
// $Id: //poco/1.4/IoT/OPC/include/Poco/JS/OPC/ClientWrapper.h#6 $
//
// Library: OPC
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


#ifndef IoT_JS_OPC_ClientWrapper_INCLUDED
#define IoT_JS_OPC_ClientWrapper_INCLUDED


#include "IoT/OPC/OPC.h"
#include "Poco/JS/Core/Wrapper.h"
#include "IoT/OPC/Client.h"


namespace IoT {
namespace OPC {


class OPC_API ClientHolder
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

	
	Client& client()
	{
		return _client;
	}

private:
	Client _client;
};


class OPC_API ClientWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for OPC Client.
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


} } // namespace IoT::OPC


#endif // IoT_JS_OPC_ClientWrapper_INCLUDED
