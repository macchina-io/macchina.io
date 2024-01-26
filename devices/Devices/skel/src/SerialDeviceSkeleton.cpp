//
// SerialDeviceSkeleton.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/SerialDeviceSkeleton.h"
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


class SerialDeviceGetFeatureMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getFeature"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->getFeature(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getFeatureReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getFeature"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getFeature"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getFeature"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyBoolMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyBool"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->getPropertyBool(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyBoolReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyBool"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyBool"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyBool"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyDoubleMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyDouble"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			double remoting__return = remoting__pCastedRO->getPropertyDouble(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyDoubleReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<double >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyDouble"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyDouble"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyDouble"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyIntMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyInt"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			int remoting__return = remoting__pCastedRO->getPropertyInt(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyIntReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<int >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyInt16MethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyInt16"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			Poco::Int16 remoting__return = remoting__pCastedRO->getPropertyInt16(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyInt16Reply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::Int16 >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt16"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt16"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt16"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyInt64MethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyInt64"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			Poco::Int64 remoting__return = remoting__pCastedRO->getPropertyInt64(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyInt64Reply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::Int64 >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt64"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt64"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyInt64"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyStringMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyString"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			std::string remoting__return = remoting__pCastedRO->getPropertyString(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyStringReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyString"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetPropertyTimestampMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getPropertyTimestamp"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			Poco::Timestamp remoting__return = remoting__pCastedRO->getPropertyTimestamp(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getPropertyTimestampReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::Timestamp >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::getPropertyTimestamp"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::getPropertyTimestamp"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::getPropertyTimestamp"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceHasFeatureMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"hasFeature"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->hasFeature(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("hasFeatureReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::hasFeature"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::hasFeature"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::hasFeature"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceHasPropertyMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"hasProperty"s,"name"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->hasProperty(name);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("hasPropertyReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::hasProperty"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::hasProperty"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::hasProperty"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetFeatureMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setFeature"s,"name"s,"enable"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			bool enable;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[2], true, remoting__deser, enable);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setFeature(name, enable);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setFeatureReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setFeature"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setFeature"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setFeature"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyBoolMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyBool"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			bool value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyBool(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyBoolReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyBool"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyBool"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyBool"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyDoubleMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyDouble"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			double value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<double >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyDouble(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyDoubleReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyDouble"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyDouble"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyDouble"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyIntMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyInt"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			int value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyInt(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyIntReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyInt16MethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyInt16"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			Poco::Int16 value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<Poco::Int16 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyInt16(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyInt16Reply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt16"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt16"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt16"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyInt64MethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyInt64"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			Poco::Int64 value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<Poco::Int64 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyInt64(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyInt64Reply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt64"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt64"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyInt64"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyStringMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyString"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			std::string value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyString(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyStringReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyString"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetPropertyTimestampMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setPropertyTimestamp"s,"name"s,"value"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string name;
			Poco::Timestamp value;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, name);
			Poco::RemotingNG::TypeDeserializer<Poco::Timestamp >::deserialize(REMOTING__NAMES[2], true, remoting__deser, value);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setPropertyTimestamp(name, value);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setPropertyTimestampReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::Device::setPropertyTimestamp"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::Device::setPropertyTimestamp"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::Device::setPropertyTimestamp"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceAvailableMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"available"s};
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			int remoting__return = remoting__pCastedRO->available();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("availableReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<int >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::available"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::available"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::available"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceGetRTSMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"getRTS"s};
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->getRTS();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("getRTSReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::getRTS"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::getRTS"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::getRTS"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDevicePollMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"poll"s,"timeout"s};
		bool remoting__requestSucceeded = false;
		try
		{
			double timeout;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<double >::deserialize(REMOTING__NAMES[1], true, remoting__deser, timeout);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->poll(timeout);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("pollReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::poll"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::poll"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::poll"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceReadByteMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"readByte"s};
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			Poco::UInt8 remoting__return = remoting__pCastedRO->readByte();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("readByteReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt8 >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::readByte"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::readByte"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::readByte"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceReadLineMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"readLine"s,"delimiters"s,"timeout"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string delimiters;
			double timeout;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, delimiters);
			Poco::RemotingNG::TypeDeserializer<double >::deserialize(REMOTING__NAMES[2], true, remoting__deser, timeout);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			std::string remoting__return = remoting__pCastedRO->readLine(delimiters, timeout);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("readLineReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::readLine"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::readLine"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::readLine"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceReadStringMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"readString"s};
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			std::string remoting__return = remoting__pCastedRO->readString();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("readStringReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::readString"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::readString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::readString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceReconfigureMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"reconfigure"s,"baudRate"s,"parameters"s,"flowControl"s};
		bool remoting__requestSucceeded = false;
		try
		{
			int baudRate;
			std::string parameters;
			std::string flowControl;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, remoting__deser, baudRate);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, parameters);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, flowControl);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->reconfigure(baudRate, parameters, flowControl);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("reconfigureReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::reconfigure"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::reconfigure"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::reconfigure"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceSetRTSMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setRTS"s,"status"s};
		bool remoting__requestSucceeded = false;
		try
		{
			bool status;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, status);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setRTS(status);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setRTSReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::setRTS"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::setRTS"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::setRTS"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceWriteByteMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"writeByte"s,"byte"s};
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt8 byte;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, byte);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->writeByte(byte);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("writeByteReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::writeByte"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::writeByte"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::writeByte"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class SerialDeviceWriteStringMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"writeString"s,"data"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string data;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::Devices::SerialDeviceRemoteObject* remoting__pCastedRO = static_cast<IoT::Devices::SerialDeviceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->writeString(data);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("writeStringReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::Devices::SerialDevice::writeString"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::Devices::SerialDevice::writeString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::Devices::SerialDevice::writeString"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


SerialDeviceSkeleton::SerialDeviceSkeleton():
	Poco::RemotingNG::Skeleton()

{
	using namespace std::string_literals;
	
	addMethodHandler("available"s, new IoT::Devices::SerialDeviceAvailableMethodHandler);
	addMethodHandler("getFeature"s, new IoT::Devices::SerialDeviceGetFeatureMethodHandler);
	addMethodHandler("getPropertyBool"s, new IoT::Devices::SerialDeviceGetPropertyBoolMethodHandler);
	addMethodHandler("getPropertyDouble"s, new IoT::Devices::SerialDeviceGetPropertyDoubleMethodHandler);
	addMethodHandler("getPropertyInt"s, new IoT::Devices::SerialDeviceGetPropertyIntMethodHandler);
	addMethodHandler("getPropertyInt16"s, new IoT::Devices::SerialDeviceGetPropertyInt16MethodHandler);
	addMethodHandler("getPropertyInt64"s, new IoT::Devices::SerialDeviceGetPropertyInt64MethodHandler);
	addMethodHandler("getPropertyString"s, new IoT::Devices::SerialDeviceGetPropertyStringMethodHandler);
	addMethodHandler("getPropertyTimestamp"s, new IoT::Devices::SerialDeviceGetPropertyTimestampMethodHandler);
	addMethodHandler("getRTS"s, new IoT::Devices::SerialDeviceGetRTSMethodHandler);
	addMethodHandler("hasFeature"s, new IoT::Devices::SerialDeviceHasFeatureMethodHandler);
	addMethodHandler("hasProperty"s, new IoT::Devices::SerialDeviceHasPropertyMethodHandler);
	addMethodHandler("poll"s, new IoT::Devices::SerialDevicePollMethodHandler);
	addMethodHandler("readByte"s, new IoT::Devices::SerialDeviceReadByteMethodHandler);
	addMethodHandler("readLine"s, new IoT::Devices::SerialDeviceReadLineMethodHandler);
	addMethodHandler("readString"s, new IoT::Devices::SerialDeviceReadStringMethodHandler);
	addMethodHandler("reconfigure"s, new IoT::Devices::SerialDeviceReconfigureMethodHandler);
	addMethodHandler("setFeature"s, new IoT::Devices::SerialDeviceSetFeatureMethodHandler);
	addMethodHandler("setPropertyBool"s, new IoT::Devices::SerialDeviceSetPropertyBoolMethodHandler);
	addMethodHandler("setPropertyDouble"s, new IoT::Devices::SerialDeviceSetPropertyDoubleMethodHandler);
	addMethodHandler("setPropertyInt"s, new IoT::Devices::SerialDeviceSetPropertyIntMethodHandler);
	addMethodHandler("setPropertyInt16"s, new IoT::Devices::SerialDeviceSetPropertyInt16MethodHandler);
	addMethodHandler("setPropertyInt64"s, new IoT::Devices::SerialDeviceSetPropertyInt64MethodHandler);
	addMethodHandler("setPropertyString"s, new IoT::Devices::SerialDeviceSetPropertyStringMethodHandler);
	addMethodHandler("setPropertyTimestamp"s, new IoT::Devices::SerialDeviceSetPropertyTimestampMethodHandler);
	addMethodHandler("setRTS"s, new IoT::Devices::SerialDeviceSetRTSMethodHandler);
	addMethodHandler("writeByte"s, new IoT::Devices::SerialDeviceWriteByteMethodHandler);
	addMethodHandler("writeString"s, new IoT::Devices::SerialDeviceWriteStringMethodHandler);
}


SerialDeviceSkeleton::~SerialDeviceSkeleton()
{
}


const std::string SerialDeviceSkeleton::DEFAULT_NS;
} // namespace Devices
} // namespace IoT

