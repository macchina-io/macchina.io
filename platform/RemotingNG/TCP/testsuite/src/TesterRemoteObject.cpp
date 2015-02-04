//
// TesterRemoteObject.cpp
//
// Package: Generated
// Module:  TesterRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "TesterRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "TesterEventDispatcher.h"


TesterRemoteObject::TesterRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Tester> pServiceObject):
	ITester(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->testEvent += Poco::delegate(this, &TesterRemoteObject::event__testEvent);
	_pServiceObject->testOneWayEvent += Poco::delegate(this, &TesterRemoteObject::event__testOneWayEvent);
}


TesterRemoteObject::~TesterRemoteObject()
{
	try
	{
		_pServiceObject->testEvent -= Poco::delegate(this, &TesterRemoteObject::event__testEvent);
		_pServiceObject->testOneWayEvent -= Poco::delegate(this, &TesterRemoteObject::event__testOneWayEvent);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void TesterRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
}


void TesterRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TesterEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TesterRemoteObject::remoting__hasEvents() const
{
	return true;
}


void TesterRemoteObject::event__testEvent(std::string& data)
{
	testEvent(this, data);
}


void TesterRemoteObject::event__testOneWayEvent(std::string& data)
{
	testOneWayEvent(this, data);
}


