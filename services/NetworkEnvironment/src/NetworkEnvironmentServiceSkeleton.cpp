//
// NetworkEnvironmentServiceSkeleton.cpp
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceSkeleton.h"
#include "IoT/NetworkEnvironment/NetworkInterfaceDeserializer.h"
#include "IoT/NetworkEnvironment/NetworkInterfaceSerializer.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkEnvironmentServiceEnumerateInterfacesMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"enumerateInterfaces"s,"options"s};
		bool remoting__requestSucceeded = false;
		try
		{
			int options(0);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<int>::deserialize(REMOTING__NAMES[1], false, remoting__deser, options);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject* remoting__pCastedRO = static_cast<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject*>(remoting__pRemoteObject.get());
			std::vector<IoT::NetworkEnvironment::NetworkInterface> remoting__return = remoting__pCastedRO->enumerateInterfaces(options);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("enumerateInterfacesReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::vector<IoT::NetworkEnvironment::NetworkInterface>>::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::NetworkEnvironment::NetworkEnvironmentService::enumerateInterfaces"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::NetworkEnvironment::NetworkEnvironmentService::enumerateInterfaces"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::NetworkEnvironment::NetworkEnvironmentService::enumerateInterfaces"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class NetworkEnvironmentServiceFindActiveNetworkInterfaceMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"findActiveNetworkInterface"s,"ipVersion"s};
		bool remoting__requestSucceeded = false;
		try
		{
			IoT::NetworkEnvironment::IPVersion ipVersion;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			int remoting__ipVersionTmp;
			Poco::RemotingNG::TypeDeserializer<int>::deserialize(REMOTING__NAMES[1], true, remoting__deser, remoting__ipVersionTmp);
			ipVersion = static_cast<IoT::NetworkEnvironment::IPVersion>(remoting__ipVersionTmp);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject* remoting__pCastedRO = static_cast<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject*>(remoting__pRemoteObject.get());
			std::string remoting__return = remoting__pCastedRO->findActiveNetworkInterface(ipVersion);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("findActiveNetworkInterfaceReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string>::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::NetworkEnvironment::NetworkEnvironmentService::findActiveNetworkInterface"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::NetworkEnvironment::NetworkEnvironmentService::findActiveNetworkInterface"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::NetworkEnvironment::NetworkEnvironmentService::findActiveNetworkInterface"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


NetworkEnvironmentServiceSkeleton::NetworkEnvironmentServiceSkeleton():
	Poco::RemotingNG::Skeleton()

{
	using namespace std::string_literals;
	
	addMethodHandler("enumerateInterfaces"s, new IoT::NetworkEnvironment::NetworkEnvironmentServiceEnumerateInterfacesMethodHandler);
	addMethodHandler("findActiveNetworkInterface"s, new IoT::NetworkEnvironment::NetworkEnvironmentServiceFindActiveNetworkInterfaceMethodHandler);
}


NetworkEnvironmentServiceSkeleton::~NetworkEnvironmentServiceSkeleton()
{
}


const std::string NetworkEnvironmentServiceSkeleton::DEFAULT_NS;
} // namespace NetworkEnvironment
} // namespace IoT

