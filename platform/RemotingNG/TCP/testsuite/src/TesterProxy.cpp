//
// TesterProxy.cpp
//
// Package: Generated
// Module:  TesterProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "TesterProxy.h"
#include "Class1Deserializer.h"
#include "Class1Serializer.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Struct1Deserializer.h"
#include "Struct1Serializer.h"
#include "Struct2Deserializer.h"
#include "Struct2Serializer.h"
#include "Struct3Deserializer.h"
#include "Struct3Serializer.h"
#include "Struct4Deserializer.h"
#include "Struct4Serializer.h"
#include "Struct5Deserializer.h"
#include "Struct5Serializer.h"
#include "TesterEventDispatcher.h"
#include "TesterEventSubscriber.h"


TesterProxy::TesterProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid):
	TesterRemoteObject(),
	Poco::RemotingNG::Proxy(),
	_pEventListener(),
	_pEventSubscriber(),
	_testClass11Ret(),
	_testEnum11Ret(),
	_testEnum21Ret(),
	_testInt1Ret(),
	_testNestedTypeRet(),
	_testOneWayResultRet(),
	_testPtrRet(),
	_testStruct11Ret(),
	_testStruct1Vec1Ret(),
	_testStruct21Ret(),
	_testStruct31Ret(),
	_testStruct41Ret(),
	_testStruct51Ret()
{
	remoting__init(oid);
}


TesterProxy::~TesterProxy()
{
	if (_pEventListener)
	{
		try
		{
			_pEventListener->unsubscribeFromEvents(_pEventSubscriber);
		}
		catch (...)
		{
		}
		_pEventSubscriber = 0;
		_pEventListener = 0;
	}
}


void TesterProxy::fireTestEvent(const std::string& arg)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"fireTestEvent","arg"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], arg, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.sendMessage(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
}


void TesterProxy::fireTestOneWayEvent(const std::string& arg)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"fireTestOneWayEvent","arg"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], arg, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.sendMessage(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
}


void TesterProxy::fireTestVoidEvent()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"fireTestVoidEvent"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("fireTestVoidEventReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


std::string TesterProxy::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	std::string subscriberURI;
	if ((_pEventListener && !enable) || (!_pEventListener && enable))
	{
		Poco::RemotingNG::EventListener::Ptr pEventListener = pListener.cast<Poco::RemotingNG::EventListener>();
		if (pEventListener)
		{
			if (enable)
			{
				std::string eventURI = remoting__getEventURI().empty() ? remoting__getURI().toString() : remoting__getEventURI().toString();
				_pEventSubscriber = new TesterEventSubscriber(eventURI, this);
				subscriberURI = pEventListener->subscribeToEvents(_pEventSubscriber);
				_pEventListener = pEventListener;
			}
			else if (_pEventListener == pEventListener)
			{
				try
				{
					_pEventListener->unsubscribeFromEvents(_pEventSubscriber);
				}
				catch (...)
				{
					_pEventSubscriber = 0;
					_pEventListener = 0;
					throw;
				}
				_pEventSubscriber = 0;
				_pEventListener = 0;
			}
			else throw Poco::RemotingNG::RemotingException("EventListener mismatch");
		}
		else throw Poco::RemotingNG::RemotingException("Listener is not an EventListener");
	}
	return subscriberURI;
}


void TesterProxy::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TesterEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


void TesterProxy::testAuthenticated()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testAuthenticated"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testAuthenticatedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Class1 TesterProxy::testClass11(const Class1& c1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testClass11","c1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Class1 >::serialize(REMOTING__NAMES[1], c1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testClass11Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Class1 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testClass11Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testClass11Ret;
}


void TesterProxy::testClass12(Class1& c1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testClass12","c1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Class1 >::serialize(REMOTING__NAMES[1], c1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testClass12Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Class1 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, c1);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testClass13(const Class1& c1, Class1& c2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testClass13","c1","c2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Class1 >::serialize(REMOTING__NAMES[1], c1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testClass13Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Class1 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, c2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Enum1 TesterProxy::testEnum11(Enum1 e1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testEnum11","e1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], e1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testEnum11Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	int remoting__tmpReturn;
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, remoting__tmpReturn);
	_testEnum11Ret = static_cast<Enum1>(remoting__tmpReturn);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testEnum11Ret;
}


void TesterProxy::testEnum12(Enum1& e1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testEnum12","e1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], e1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testEnum12Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	int remoting__e1Tmp;
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, remoting__deser, remoting__e1Tmp);
	e1 = static_cast<Enum1>(remoting__e1Tmp);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testEnum13(Enum1 e1, Enum1& e2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testEnum13","e1","e2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], e1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testEnum13Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	int remoting__e2Tmp;
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], true, remoting__deser, remoting__e2Tmp);
	e2 = static_cast<Enum1>(remoting__e2Tmp);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Struct1::Enum2 TesterProxy::testEnum21(Struct1::Enum2 e1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testEnum21","e1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], e1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testEnum21Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	int remoting__tmpReturn;
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, remoting__tmpReturn);
	_testEnum21Ret = static_cast<Struct1::Enum2>(remoting__tmpReturn);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testEnum21Ret;
}


void TesterProxy::testEnum22(Struct1::Enum2& e1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testEnum22","e1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], e1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testEnum22Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	int remoting__e1Tmp;
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, remoting__deser, remoting__e1Tmp);
	e1 = static_cast<Struct1::Enum2>(remoting__e1Tmp);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testEnum23(Struct1::Enum2 e1, Struct1::Enum2& e2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testEnum23","e1","e2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], e1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testEnum23Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	int remoting__e2Tmp;
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], true, remoting__deser, remoting__e2Tmp);
	e2 = static_cast<Struct1::Enum2>(remoting__e2Tmp);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testFault()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testFault"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testFaultReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


int TesterProxy::testInt1(int i)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"TestInt1","Value"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], i, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("TestInt1Response");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testInt1Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testInt1Ret;
}


void TesterProxy::testInt2(int& i)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"TestInt2","Value"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], i, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("TestInt2Response");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, remoting__deser, i);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testInt3(int i1, int& i2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"TestInt3","Value1","Value2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<int >::serialize(REMOTING__NAMES[1], i1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("TestInt3Response");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], true, remoting__deser, i2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Poco::Int64 TesterProxy::testNestedType(Poco::Int64 arg)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testNestedType","arg"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::Int64 >::serialize(REMOTING__NAMES[1], arg, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testNestedTypeReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Poco::Int64 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testNestedTypeRet);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testNestedTypeRet;
}


void TesterProxy::testOneWay(const std::string& arg)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testOneWay","arg"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], arg, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.sendMessage(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
}


std::string TesterProxy::testOneWayResult()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testOneWayResult"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testOneWayResultReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testOneWayResultRet);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testOneWayResultRet;
}


void TesterProxy::testPermission()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testPermission"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testPermissionReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Poco::SharedPtr < Struct1 > TesterProxy::testPtr(Poco::SharedPtr < Struct1 > p1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testPtr","p1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::SharedPtr < Struct1 > >::serialize(REMOTING__NAMES[1], p1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testPtrReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Poco::SharedPtr < Struct1 > >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testPtrRet);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testPtrRet;
}


Struct1 TesterProxy::testStruct11(const Struct1& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct11","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct1 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct11Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct1 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testStruct11Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testStruct11Ret;
}


void TesterProxy::testStruct12(Struct1& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct12","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct1 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct12Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct1 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, s1);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testStruct13(const Struct1& s1, Struct1& s2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct13","s1","s2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct1 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct13Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct1 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, s2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


std::vector < Struct1 > TesterProxy::testStruct1Vec1(const std::vector < Struct1 >& vec)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct1Vec1","vec"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::vector < Struct1 > >::serialize(REMOTING__NAMES[1], vec, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct1Vec1Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	_testStruct1Vec1Ret.clear();
	Poco::RemotingNG::TypeDeserializer<std::vector < Struct1 > >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testStruct1Vec1Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testStruct1Vec1Ret;
}


void TesterProxy::testStruct1Vec2(std::vector < Struct1 >& vec)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct1Vec2","vec"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::vector < Struct1 > >::serialize(REMOTING__NAMES[1], vec, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct1Vec2Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::vector < Struct1 > >::deserialize(REMOTING__NAMES[1], true, remoting__deser, vec);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testStruct1Vec3(const std::vector < Struct1 >& vec1, std::vector < Struct1 >& vec2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct1Vec3","vec1","vec2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::vector < Struct1 > >::serialize(REMOTING__NAMES[1], vec1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct1Vec3Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::vector < Struct1 > >::deserialize(REMOTING__NAMES[2], true, remoting__deser, vec2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Struct2 TesterProxy::testStruct21(const Struct2& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct21","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct2 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct21Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct2 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testStruct21Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testStruct21Ret;
}


void TesterProxy::testStruct22(Struct2& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct22","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct2 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct22Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct2 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, s1);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testStruct23(const Struct2& s1, Struct2& s2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct23","s1","s2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct2 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct23Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct2 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, s2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Struct3 TesterProxy::testStruct31(const Struct3& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct31","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct3 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct31Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct3 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testStruct31Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testStruct31Ret;
}


void TesterProxy::testStruct32(Struct3& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct32","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct3 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct32Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct3 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, s1);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testStruct33(const Struct3& s1, Struct3& s2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct33","s1","s2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct3 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct33Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct3 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, s2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Struct4 TesterProxy::testStruct41(const Struct4& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct41","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct4 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct41Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct4 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testStruct41Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testStruct41Ret;
}


void TesterProxy::testStruct42(Struct4& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct42","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct4 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct42Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct4 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, s1);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testStruct43(const Struct4& s1, Struct4& s2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct43","s1","s2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct4 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct43Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct4 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, s2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


Struct5 TesterProxy::testStruct51(const Struct5& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct51","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct5 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct51Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct5 >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _testStruct51Ret);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
	return _testStruct51Ret;
}


void TesterProxy::testStruct52(Struct5& s1)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct52","s1"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct5 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct52Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct5 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, s1);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testStruct53(const Struct5& s1, Struct5& s2)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testStruct53","s1","s2"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Struct5 >::serialize(REMOTING__NAMES[1], s1, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Struct5 >::serialize(REMOTING__NAMES[2], s2, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testStruct53Reply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Struct5 >::deserialize(REMOTING__NAMES[2], true, remoting__deser, s2);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testSynchronized()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testSynchronized"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::FastMutex::ScopedLock remoting__lock(remoting__mutex());
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testSynchronizedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testSynchronizedProxy()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testSynchronizedProxy"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::FastMutex::ScopedLock remoting__lock(remoting__mutex());
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testSynchronizedProxyReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void TesterProxy::testSynchronizedRemote()
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"testSynchronizedRemote"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("testSynchronizedRemoteReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


const std::string TesterProxy::DEFAULT_NS("urn:appinf.com:service:Tester:1");
