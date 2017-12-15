//
// BridgeWrapper.h
//
// Library: JS/Bridge
// Package: Bridging
// Module:  BridgeWrapper
//
// Definition of the BridgeWrapper class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Bridge_BridgeWrapper_INCLUDED
#define JS_Bridge_BridgeWrapper_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/AtomicCounter.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <map>
#include <set>


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API BridgeHolder: public Poco::RefCountedObject
	/// This is used by the BridgeWrapper to hold information
	/// about the bridged object, including it's Remoting URI and
	/// information necessary for implementing event callbacks.
{
public:
	typedef Poco::AutoPtr<BridgeHolder> Ptr;
	
	BridgeHolder(const std::string& uri);
		/// Creates the BridgeHolder.
		
	~BridgeHolder();
		/// Destroys the BridgeHolder.
		
	const std::string& uri() const;
		/// Returns the Remoting URI.
		
	const std::string& subscriberURI() const;
		/// Returns the event subscriber URI.
		
	void setPersistent(const v8::Persistent<v8::Object>& jsObject);
		/// Sets the associated JavaScript object.
		
	v8::Persistent<v8::Object>& getPersistent();
		/// Returns the associated JavaScript object.

	void enableEvents();
		/// Enables remote events by setting up the necessary
		/// Remoting machinery to deliver events.
	
	void fireEvent(const std::string& event, const std::string& args);
		/// Fires the event with the given name in the
		/// JavaScript environment.
		
	void clear();
		/// Resets the associated JavaScript object.
		
	void enableEvent(const std::string& event);
		/// Adds the given event to the set of handled events.
		
	void disableEvent(const std::string& event);
		/// Removes the given event from the set of handled events.
		
	bool handleEvent(const std::string& event);
		/// Returns true if the given event is handled.
		
	static Ptr find(const std::string& subscriberURI);
		/// Finds the Holder in the global holder map.

protected:
	void onExecutorStopped();
	
protected:
	void registerHolder();
	void unregisterHolder();
	void disableEvents();
	
	static void destruct(const v8::WeakCallbackInfo<BridgeHolder>& data);

private:
	typedef std::map<std::string, BridgeHolder*> HolderMap;

	Poco::JS::Core::JSExecutor::Ptr _pExecutor;
	std::string _uri;
	std::string _subscriberURI;
	v8::Persistent<v8::Object> _persistent;
	Poco::RemotingNG::EventDispatcher::Ptr _pEventDispatcher;
	std::set<std::string> _handledEvents;
	
	static Poco::AtomicCounter _counter;
	static HolderMap _holderMap;
	static Poco::FastMutex _holderMapMutex;
};


class JSBridge_API BridgeWrapper: public Poco::JS::Core::Wrapper
{
public:
	BridgeWrapper();
		/// Creates the BridgeWrapper.
	
	~BridgeWrapper();
		/// Destroys the BridgeWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.
		
	static void registerTransportFactory();
		/// Registers the RemotingNG TransportFactory for the Bridge Transport.

	static void unregisterTransportFactory();
		/// Unregisters the RemotingNG TransportFactory for the Bridge Transport.
		
	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void getProperty(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setProperty(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void bridgeFunction(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void on(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toJSON(const v8::FunctionCallbackInfo<v8::Value>& args);
};


//
// inlines
//


inline const std::string& BridgeHolder::uri() const
{
	return _uri;
}


inline const std::string& BridgeHolder::subscriberURI() const
{
	return _subscriberURI;
}


inline v8::Persistent<v8::Object>& BridgeHolder::getPersistent()
{
	return _persistent;
}


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_BridgeWrapper_INCLUDED
