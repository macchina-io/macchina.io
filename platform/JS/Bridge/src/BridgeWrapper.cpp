//
// BridgeWrapper.cpp
//
// Library: JS/Bridge
// Package: Bridging
// Module:  BridgeWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Bridge/BridgeWrapper.h"
#include "Poco/JS/Bridge/Listener.h"
#include "Poco/JS/Bridge/Serializer.h"
#include "Poco/JS/Bridge/Deserializer.h"
#include "Poco/JS/Bridge/TaggedBinarySerializer.h"
#include "Poco/JS/Bridge/TaggedBinaryReader.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/Transport.h"
#include "Poco/RemotingNG/TransportFactory.h"
#include "Poco/RemotingNG/TransportFactoryManager.h"
#include "Poco/RemotingNG/Context.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/MemoryStream.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/Delegate.h"
#include "Poco/Logger.h"
#include <sstream>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Bridge {


//
// Transport
//


class Transport: public Poco::RemotingNG::Transport
{
public:
	Transport():
		_logger(Poco::Logger::get("JS.Bridge.Transport"s))
	{
	}

	~Transport()
	{
	}

	// Transport
	const std::string& endPoint() const
	{
		return _endPoint;
	}

	void connect(const std::string& endPoint)
	{
		_endPoint = endPoint;
	}

	void disconnect()
	{
		_endPoint.clear();
	}

	bool connected() const
	{
		return !_endPoint.empty();
	}

	Poco::RemotingNG::Serializer& beginMessage(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
	{
		poco_assert_dbg (messageType == Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);

		_pStream = new std::stringstream;
		_serializer.setup(*_pStream);
		return _serializer;
	}

	void sendMessage(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
	{
		poco_assert_dbg (messageType == Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);

		std::string args = _pStream->str();
		BridgeHolder::Ptr pBridgeHolder = BridgeHolder::find(_endPoint);
		if (pBridgeHolder)
		{
			pBridgeHolder->fireEvent(messageName, args);
		}
	}

	Poco::RemotingNG::Serializer& beginRequest(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
	{
		_logger.error("Cannot deliver event %s in class %s. Event has a non-const argument and is not declared oneway."s, messageName, tid);
		throw Poco::NotImplementedException("beginRequest() not implemented for jsbridge Transport");
	}

	Poco::RemotingNG::Deserializer& sendRequest(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
	{
		throw Poco::NotImplementedException("sendRequest() not implemented for jsbridge Transport");
	}

	void endRequest()
	{
		throw Poco::NotImplementedException("endRequest() not implemented for jsbridge Transport");
	}

	static const std::string PROTOCOL;

private:
	std::string _endPoint;
	Poco::SharedPtr<std::stringstream> _pStream;
	TaggedBinarySerializer _serializer;
	Poco::Logger& _logger;
};


const std::string Transport::PROTOCOL("jsbridge");


//
// TransportFactory
//


class TransportFactory: public Poco::RemotingNG::TransportFactory
{
public:
	TransportFactory()
	{
	}

	~TransportFactory()
	{
	}

	Poco::RemotingNG::Transport* createTransport()
	{
		return new Transport;
	}

	static void registerFactory()
	{
		Poco::RemotingNG::TransportFactoryManager::instance().registerFactory(Transport::PROTOCOL, new TransportFactory);
	}

	static void unregisterFactory()
	{
		Poco::RemotingNG::TransportFactoryManager::instance().unregisterFactory(Transport::PROTOCOL);
	}
};


//
// ServerTransport
//


class ServerTransport: public Poco::RemotingNG::ServerTransport
{
public:
	ServerTransport(Deserializer& deserializer, Serializer& serializer):
		_deserializer(deserializer),
		_serializer(serializer)
	{
	}

	~ServerTransport()
	{
	}

	// ServerTransport
	Deserializer& beginRequest()
	{
		return _deserializer;
	}

	Serializer& sendReply(Poco::RemotingNG::SerializerBase::MessageType /*messageType*/)
	{
		return _serializer;
	}

	void endRequest()
	{
	}

private:
	Deserializer& _deserializer;
	Serializer& _serializer;
};


//
// EventTask
//


class EventTask: public Poco::Util::TimerTask
{
public:
	EventTask(Poco::JS::Core::TimedJSExecutor::Ptr pExecutor, v8::Persistent<v8::Object>& jsObject, const std::string& event, const std::string& args):
		_pExecutor(pExecutor),
		_jsObject(jsObject),
		_event(event),
		_args(args)
	{
	}

	~EventTask()
	{
	}

	void run()
	{
		v8::Isolate* pIsolate = _pExecutor->isolate();

		v8::Locker locker(pIsolate);
		v8::Isolate::Scope isoScope(pIsolate);
		v8::HandleScope handleScope(pIsolate);
		v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _pExecutor->scriptContext()));
		v8::Context::Scope contextScope(context);

		{
			TaggedBinaryReader reader(pIsolate);
			Poco::MemoryInputStream istr(_args.data(), _args.size());
			v8::Handle<v8::Value> args[1];
			v8::Local<v8::Object> eventArg = v8::Local<v8::Object>::New(pIsolate, reader.read(istr));
			v8::Local<v8::Object> sourceArg(v8::Local<v8::Object>::New(pIsolate, _jsObject));
			V8_CHECK_SET_RESULT(eventArg->Set(context, Core::Wrapper::toV8Internalized(pIsolate, "source"s), sourceArg));
			args[0] = eventArg;
			_pExecutor->callInContext(pIsolate, context, _jsObject, _event, 1, args);
		}
	}

private:
	Poco::JS::Core::TimedJSExecutor::Ptr _pExecutor;
	v8::Persistent<v8::Object>& _jsObject;
	std::string _event;
	std::string _args;
};


//
// BridgeHolder
//


Poco::AtomicCounter BridgeHolder::_counter;
BridgeHolder::HolderMap BridgeHolder::_holderMap;
Poco::FastMutex BridgeHolder::_holderMapMutex;


BridgeHolder::BridgeHolder(const std::string& uri):
	_pExecutor(Poco::JS::Core::JSExecutor::current()),
	_uri(uri)
{
	_subscriberURI += "jsbridge://local/jsbridge/Bridge/";
	int id = ++_counter;
	Poco::NumberFormatter::append(_subscriberURI, id);
	registerHolder();

	_pExecutor->stopped += Poco::delegate(this, &BridgeHolder::onExecutorStopped);
}


BridgeHolder::~BridgeHolder()
{
	try
	{
		if (_pExecutor)
		{
			_pExecutor->stopped -= Poco::delegate(this, &BridgeHolder::onExecutorStopped);
		}

		unregisterHolder();
		clear();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void BridgeHolder::setPersistent(const v8::Persistent<v8::Object>& jsObject)
{
	_persistent.Reset(_pExecutor->isolate(), jsObject);
	if (!_persistent.IsEmpty())
	{
		_persistent.SetWeak();
	}
}


void BridgeHolder::clear()
{
	_persistent.Reset();

	try
	{
		disableEvents();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void BridgeHolder::fireEvent(const std::string& event, const std::string& args)
{
	if (_pExecutor && handleEvent(event))
	{
		Poco::JS::Core::TimedJSExecutor::Ptr pTimedExecutor = _pExecutor.cast<Poco::JS::Core::TimedJSExecutor>();
		if (pTimedExecutor)
		{
			EventTask::Ptr pEventTask = new EventTask(pTimedExecutor, _persistent, event, args);
			pTimedExecutor->schedule(pEventTask);
		}
	}
}


BridgeHolder::Ptr BridgeHolder::find(const std::string& subscriberURI)
{
	Poco::FastMutex::ScopedLock lock(_holderMapMutex);

	HolderMap::iterator it = _holderMap.find(subscriberURI);
	if (it != _holderMap.end())
		return Ptr(it->second, true);
	else
		return Ptr();
}


void BridgeHolder::enableEvents()
{
	if (!_pEventDispatcher)
	{
		Poco::RemotingNG::Identifiable::Ptr pIdentifiable = Poco::RemotingNG::ORB::instance().findObject(_uri);
		Poco::RemotingNG::RemoteObject::Ptr pRemoteObject = pIdentifiable.cast<Poco::RemotingNG::RemoteObject>();
		if (pRemoteObject && pRemoteObject->remoting__hasEvents())
		{
			_pEventDispatcher = Poco::RemotingNG::ORB::instance().findEventDispatcher(_uri, "jsbridge"s);
			if (_pEventDispatcher)
			{
				_pEventDispatcher->subscribe(_subscriberURI, _subscriberURI);
			}
		}
	}
}


void BridgeHolder::disableEvents()
{
	if (_pEventDispatcher)
	{
		_pEventDispatcher->unsubscribe(_subscriberURI);
		_pEventDispatcher.reset();
	}
}


void BridgeHolder::registerHolder()
{
	Poco::FastMutex::ScopedLock lock(_holderMapMutex);

	_holderMap[_subscriberURI] = this;
}


void BridgeHolder::unregisterHolder()
{
	Poco::FastMutex::ScopedLock lock(_holderMapMutex);

	_holderMap.erase(_subscriberURI);
}


void BridgeHolder::onExecutorStopped()
{
	disableEvents();
	if (_pExecutor)
	{
		_pExecutor->stopped -= Poco::delegate(this, &BridgeHolder::onExecutorStopped);
	}
	_pExecutor = 0;
}


void BridgeHolder::enableEvent(const std::string& event)
{
	_handledEvents.insert(event);
}


void BridgeHolder::disableEvent(const std::string& event)
{
	_handledEvents.erase(event);
}


bool BridgeHolder::handleEvent(const std::string& event)
{
	return _handledEvents.count(event) > 0;
}


//
// BridgeWrapper
//


BridgeWrapper::BridgeWrapper()
{
}


BridgeWrapper::~BridgeWrapper()
{
}


v8::Handle<v8::FunctionTemplate> BridgeWrapper::constructor(v8::Isolate* pIsolate)
{
	return v8::FunctionTemplate::New(pIsolate, construct);
}


v8::Handle<v8::ObjectTemplate> BridgeWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Bridge.Bridge"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);

		v8::NamedPropertyHandlerConfiguration nph(getProperty);
		nph.flags = static_cast<v8::PropertyHandlerFlags>(static_cast<int>(v8::PropertyHandlerFlags::kOnlyInterceptStrings) | static_cast<int>(v8::PropertyHandlerFlags::kNonMasking));
		objectTemplate->SetHandler(nph);

		objectTemplate->Set(toV8Internalized(pIsolate, "on"s), v8::FunctionTemplate::New(pIsolate, on));
		objectTemplate->Set(toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toJSON));

		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "$uri"s), getURI);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "$sub"s), getSub);

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> bridgeWrapperTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(bridgeWrapperTemplate);
}


void BridgeWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	BridgeHolder::Ptr pHolder;
	try
	{
		if (args.Length() == 1)
		{
			pHolder = new BridgeHolder(toString(pIsolate, args[0]));
		}
		else
		{
			returnException(args, "invalid or missing arguments; object URI required"s);
			return;
		}

		BridgeWrapper wrapper;
		v8::Persistent<v8::Object>& bridgeObject(wrapper.wrapNativePersistent(pIsolate, pHolder));
		if (!bridgeObject.IsEmpty())
		{
			pHolder->setPersistent(bridgeObject);
		}
		v8::Local<v8::Object> localBridgeObject = v8::Local<v8::Object>::New(pIsolate, bridgeObject);
		args.GetReturnValue().Set(localBridgeObject);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BridgeWrapper::getProperty(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	v8::Local<v8::Object> object = info.Holder();
	if (object->HasRealNamedProperty(context, property).FromMaybe(false))
	{
		v8::MaybeLocal<v8::Value> maybeProp = object->GetRealNamedProperty(pIsolate->GetCurrentContext(), property);
		v8::Local<v8::Value> prop;
		if (maybeProp.ToLocal(&prop))
		{
			info.GetReturnValue().Set(prop);
		}
	}
	else
	{
		v8::MaybeLocal<v8::String> maybeName = property->ToString(context);
		v8::Local<v8::String> name;
		if (maybeName.ToLocal(&name))
		{
			v8::MaybeLocal<v8::Function> maybeFunction = v8::Function::New(context, bridgeFunction, name);
			v8::Local<v8::Function> function;
			if (maybeFunction.ToLocal(&function))
			{
				function->SetName(name);
				info.GetReturnValue().Set(function);
			}
		}
	}
}


void BridgeWrapper::bridgeFunction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	BridgeHolder* pHolder = Wrapper::unwrapNative<BridgeHolder>(args);
	if (pHolder)
	{
		try
		{
			v8::Local<v8::String> name = v8::Local<v8::String>::Cast(args.Data());
			std::string method(toString(pIsolate, name));
			if (method.compare(0, 2, "__"s) == 0)
			{
				method.erase(0, 2);
			}
			v8::Local<v8::Object> argsArray = v8::Array::New(pIsolate, args.Length());
			for (int i = 0; i < args.Length(); i++)
			{
				V8_CHECK_SET_RESULT(argsArray->Set(context, i, args[i]));
			}

			Poco::RemotingNG::ScopedContext scopedContext;
			scopedContext.context()->setValue("transport"s, Transport::PROTOCOL);
			scopedContext.context()->setValue("uri"s, pHolder->uri());

			Deserializer deserializer(method, Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST, pIsolate, argsArray);
			Serializer serializer(pIsolate);
			ServerTransport transport(deserializer, serializer);
			Listener listener;
			if (!Poco::RemotingNG::ORB::instance().invoke(listener, pHolder->uri(), transport))
			{
				returnException(args, "object not found: "s + pHolder->uri());
			}
			else if (serializer.exception())
			{
				returnException(args, *serializer.exception());
			}
			else
			{
				v8::Local<v8::Object> returnObject(v8::Local<v8::Object>::New(pIsolate, serializer.jsValue()));
				v8::Local<v8::String> returnParam = Core::Wrapper::toV8String(pIsolate, Poco::RemotingNG::SerializerBase::RETURN_PARAM);
				if (serializer.totalSerialized() == 1 && returnObject->Has(context, returnParam).FromMaybe(false))
				{
					v8::MaybeLocal<v8::Value> maybeReturnValue = returnObject->Get(context, returnParam);
					v8::Local<v8::Value> returnValue;
					if (maybeReturnValue.ToLocal(&returnValue))
					{
						args.GetReturnValue().Set(returnValue);
					}
				}
				else
				{
					args.GetReturnValue().Set(returnObject);
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
	else returnException(args, "no object - bridge function cannot be called as standalone function"s);
}


void BridgeWrapper::on(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	v8::Local<v8::Object> object = args.Holder();
	if (args.Length() >= 1)
	{
		if (args[0]->IsString())
		{
			v8::Local<v8::String> name = v8::Local<v8::String>::Cast(args[0]);
			if (args.Length() >= 2 && args[1]->IsFunction())
			{
				V8_CHECK_SET_RESULT(object->Set(context, name, args[1]));
				BridgeHolder* pHolder = Wrapper::unwrapNative<BridgeHolder>(args);
				try
				{
					poco_check_ptr (pHolder);
					pHolder->enableEvents();
					pHolder->enableEvent(toString(pIsolate, args[0]));
				}
				catch (Poco::Exception& exc)
				{
					returnException(args, exc);
				}
			}
			else if (args.Length() >= 2 && args[1]->IsNull())
			{
				V8_CHECK_SET_RESULT(object->Set(context, name, args[1]));
				BridgeHolder* pHolder = Wrapper::unwrapNative<BridgeHolder>(args);
				try
				{
					poco_check_ptr (pHolder);
					pHolder->disableEvent(toString(pIsolate, args[0]));
				}
				catch (Poco::Exception& exc)
				{
					returnException(args, exc);
				}
			}
			else if (args.Length() >= 2)
			{
				returnException(args, "Invalid argument: Second argument to on() must be a function"s);
			}
			else
			{
				v8::MaybeLocal<v8::Value> maybePropValue = object->GetRealNamedProperty(context, name);
				v8::Local<v8::Value> propValue;
				if (maybePropValue.ToLocal(&propValue))
				{
					args.GetReturnValue().Set(propValue);
				}
			}
		}
		else
		{
			returnException(args, "Invalid argument: First argument to on() must be event name"s);
		}
	}
}


void BridgeWrapper::toJSON(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	BridgeHolder* pHolder = Wrapper::unwrapNative<BridgeHolder>(args);
	const std::string& uri = pHolder->uri();
	const std::string& sub = pHolder->subscriberURI();

	v8::Local<v8::Object> object = v8::Object::New(pIsolate);
	V8_CHECK_SET_RESULT(object->Set(context, Core::Wrapper::toV8Internalized(pIsolate, "$uri"s), Core::Wrapper::toV8String(pIsolate, uri)));
	V8_CHECK_SET_RESULT(object->Set(context, Core::Wrapper::toV8Internalized(pIsolate, "$sub"s), Core::Wrapper::toV8String(pIsolate, sub)));

	args.GetReturnValue().Set(object);
}


void BridgeWrapper::getURI(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	BridgeHolder* pHolder = Wrapper::unwrapNative<BridgeHolder>(info);
	returnString(info, pHolder->uri());
}


void BridgeWrapper::getSub(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	BridgeHolder* pHolder = Wrapper::unwrapNative<BridgeHolder>(info);
	returnString(info, pHolder->subscriberURI());
}


void BridgeWrapper::registerTransportFactory()
{
	TransportFactory::registerFactory();
}


void BridgeWrapper::unregisterTransportFactory()
{
	TransportFactory::unregisterFactory();
}


} } } // namespace Poco::JS::Bridge
