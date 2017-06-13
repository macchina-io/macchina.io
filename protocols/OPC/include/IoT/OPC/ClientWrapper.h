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
#include "Poco/Dynamic/Var.h"


namespace IoT {
namespace OPC {


class OPC_API ClientHolder
{
public:
	ClientHolder(const std::string& server,
		Poco::Logger* pLogger,
		int port = OPC_STANDARD_PORT,
		const std::string& user = "",
		const std::string& pass = "",
		bool doConnect = true,
		bool typeSafe = true,
		const std::string& proto = "opc.tcp");
		/// Creates the ClientHolder.
		
	~ClientHolder();
		/// Destroys the ClientHolder.

	
	Client& client();
		/// Returns reference to OPC client.

	template <typename T, typename V, typename N>
	void writeInteger(const V& arg, int nsIndex, const N& nodeID)
	{
		Poco::Dynamic::Var var = arg->IntegerValue();
		T value = var.convert<T>();
		_client.write(nsIndex, nodeID, value);
	}

	template <typename T, typename V, typename N>
	void writeFloat(const V& arg, int nsIndex, const N& nodeID)
	{
		Poco::Dynamic::Var var = arg->NumberValue();
		T value = var.convert<T>();
		_client.write(nsIndex, nodeID, value);
	}

private:
	Client _client;
};


inline Client& ClientHolder::client()
{
	return _client;
}


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
	static void write(const v8::FunctionCallbackInfo<v8::Value>& args);

private:

	template <typename N, typename T>
	static void write(int nsIndex, const T& id, const v8::FunctionCallbackInfo<v8::Value>& args, int idx)
	{
		ClientHolder* pClientHolder = Wrapper::unwrapNative<ClientHolder>(args);
		if(pClientHolder)
		{
			Client& client = pClientHolder->client();
			NodeType nt = client.getValueType<N>(nsIndex, id);
			if(nt._type != Client::OPC_NODE_NOT_FOUND)
			{
				if(!nt._isArray)
				{
					switch(nt._type)
					{
						case UA_TYPES_BOOLEAN:
						{
							bool value = args[idx]->BooleanValue();
							client.write(nsIndex, id, value);
							break;
						}
						case UA_TYPES_SBYTE:  { pClientHolder->writeInteger<Poco::Int8>(args[idx], nsIndex, id);   break; }
						case UA_TYPES_BYTE:   { pClientHolder->writeInteger<Poco::UInt8>(args[idx], nsIndex, id);  break; }
						case UA_TYPES_INT16:  { pClientHolder->writeInteger<Poco::Int16>(args[idx], nsIndex, id);  break; }
						case UA_TYPES_UINT16: { pClientHolder->writeInteger<Poco::UInt16>(args[idx], nsIndex, id); break; }
						case UA_TYPES_INT32:  { pClientHolder->writeInteger<Poco::Int32>(args[idx], nsIndex, id);  break; }
						case UA_TYPES_UINT32: { pClientHolder->writeInteger<Poco::UInt32>(args[idx], nsIndex, id); break; }
						case UA_TYPES_INT64:  { pClientHolder->writeInteger<Poco::Int64>(args[idx], nsIndex, id);  break; }
						case UA_TYPES_UINT64: { pClientHolder->writeInteger<Poco::UInt64>(args[idx], nsIndex, id); break; }
						case UA_TYPES_FLOAT:  { pClientHolder->writeFloat<float>(args[idx], nsIndex, id);  break; }
						case UA_TYPES_DOUBLE: { pClientHolder->writeFloat<double>(args[idx], nsIndex, id); break; }
						case UA_TYPES_DATETIME:
						{
							//TODO
						}
						case UA_TYPES_STRING:
						{
							client.write(nsIndex, id, std::string(*v8::String::Utf8Value(args[idx]->ToString())));
							break;
						}
					default:
						returnException(args, "Type not supported:" + Poco::NumberFormatter::format(nt._type));
						return;
					}
				}
				else
				{
					returnException(args, "Node not found:" + N(nsIndex, id).toString());
					return;
				}
			}
		}
	}
};


} } // namespace IoT::OPC


#endif // IoT_JS_OPC_ClientWrapper_INCLUDED
