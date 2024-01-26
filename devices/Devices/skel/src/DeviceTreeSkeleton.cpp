//
// DeviceTreeSkeleton.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceTreeSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceTreeSkeleton.h"
#include "IoT/Devices/DeviceNodeDeserializer.h"
#include "IoT/Devices/DeviceNodeSerializer.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class DeviceTreeDeviceByIdMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"deviceById"s,"id"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string id;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, id);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::DeviceTreeRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::DeviceTreeRemoteObject*>(remoting__pRemoteObject.get());
			IoT::Devices::DeviceNode remoting__return = remoting__pCastedRO->deviceById(id);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("deviceByIdReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<IoT::Devices::DeviceNode >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::DeviceTree::deviceById"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::DeviceTree::deviceById"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::DeviceTree::deviceById"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class DeviceTreeDeviceByPathMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"deviceByPath"s,"path"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string path;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, path);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::DeviceTreeRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::DeviceTreeRemoteObject*>(remoting__pRemoteObject.get());
			IoT::Devices::DeviceNode remoting__return = remoting__pCastedRO->deviceByPath(path);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("deviceByPathReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<IoT::Devices::DeviceNode >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::DeviceTree::deviceByPath"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::DeviceTree::deviceByPath"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::DeviceTree::deviceByPath"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class DeviceTreeFindDeviceByIdMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"findDeviceById"s,"id"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string id;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, id);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::DeviceTreeRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::DeviceTreeRemoteObject*>(remoting__pRemoteObject.get());
			Poco::Optional < IoT::Devices::DeviceNode > remoting__return = remoting__pCastedRO->findDeviceById(id);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("findDeviceByIdReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::Optional < IoT::Devices::DeviceNode > >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::DeviceTree::findDeviceById"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::DeviceTree::findDeviceById"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::DeviceTree::findDeviceById"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class DeviceTreeFindDeviceByPathMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"findDeviceByPath"s,"path"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string path;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, path);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::DeviceTreeRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::DeviceTreeRemoteObject*>(remoting__pRemoteObject.get());
			Poco::Optional < IoT::Devices::DeviceNode > remoting__return = remoting__pCastedRO->findDeviceByPath(path);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("findDeviceByPathReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::Optional < IoT::Devices::DeviceNode > >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::DeviceTree::findDeviceByPath"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::DeviceTree::findDeviceByPath"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::DeviceTree::findDeviceByPath"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


DeviceTreeSkeleton::DeviceTreeSkeleton():
	Poco::RemotingNG::Skeleton()

{
	using namespace std::string_literals;
	
	addMethodHandler("deviceById"s, new IoT::Devices::DeviceTreeDeviceByIdMethodHandler);
	addMethodHandler("deviceByPath"s, new IoT::Devices::DeviceTreeDeviceByPathMethodHandler);
	addMethodHandler("findDeviceById"s, new IoT::Devices::DeviceTreeFindDeviceByIdMethodHandler);
	addMethodHandler("findDeviceByPath"s, new IoT::Devices::DeviceTreeFindDeviceByPathMethodHandler);
}


DeviceTreeSkeleton::~DeviceTreeSkeleton()
{
}


const std::string DeviceTreeSkeleton::DEFAULT_NS;
} // namespace Devices
} // namespace IoT

