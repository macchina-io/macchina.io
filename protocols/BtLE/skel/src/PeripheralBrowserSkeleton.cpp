//
// PeripheralBrowserSkeleton.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralBrowserSkeleton.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserBrowseMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"browse"s,"activeScan"s};
		bool remoting__requestSucceeded = false;
		try
		{
			bool activeScan(false);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], false, remoting__deser, activeScan);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::BtLE::PeripheralBrowserRemoteObject* remoting__pCastedRO = static_cast<IoT::BtLE::PeripheralBrowserRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->browse(activeScan);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("browseReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::browse"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::browse"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::browse"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PeripheralBrowserBrowseInProgressMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"browseInProgress"s};
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::BtLE::PeripheralBrowserRemoteObject* remoting__pCastedRO = static_cast<IoT::BtLE::PeripheralBrowserRemoteObject*>(remoting__pRemoteObject.get());
			bool remoting__return = remoting__pCastedRO->browseInProgress();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("browseInProgressReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::browseInProgress"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::browseInProgress"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::browseInProgress"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PeripheralBrowserCancelBrowseMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"cancelBrowse"s};
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::BtLE::PeripheralBrowserRemoteObject* remoting__pCastedRO = static_cast<IoT::BtLE::PeripheralBrowserRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->cancelBrowse();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("cancelBrowseReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::cancelBrowse"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::cancelBrowse"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::BtLE::PeripheralBrowser::cancelBrowse"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


PeripheralBrowserSkeleton::PeripheralBrowserSkeleton():
	Poco::RemotingNG::Skeleton()

{
	using namespace std::string_literals;
	
	addMethodHandler("browse"s, new IoT::BtLE::PeripheralBrowserBrowseMethodHandler);
	addMethodHandler("browseInProgress"s, new IoT::BtLE::PeripheralBrowserBrowseInProgressMethodHandler);
	addMethodHandler("cancelBrowse"s, new IoT::BtLE::PeripheralBrowserCancelBrowseMethodHandler);
}


PeripheralBrowserSkeleton::~PeripheralBrowserSkeleton()
{
}


const std::string PeripheralBrowserSkeleton::DEFAULT_NS;
} // namespace BtLE
} // namespace IoT

