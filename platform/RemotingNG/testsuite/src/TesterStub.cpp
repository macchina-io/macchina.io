//
// TesterStub.cpp
//
// Package: Generated
// Module:  TesterStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "TesterStub.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "TesterEventDispatcher.h"


TesterStub::TesterStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Tester> pServiceObject):
	TesterRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->testEvent += Poco::delegate(this, &TesterStub::event__testEvent);
	_pServiceObject->testFilteredEvent += Poco::delegate(this, &TesterStub::event__testFilteredEvent);
	_pServiceObject->testOneWayEvent += Poco::delegate(this, &TesterStub::event__testOneWayEvent);
	_pServiceObject->testVoidEvent += Poco::delegate(this, &TesterStub::event__testVoidEvent);
}


TesterStub::~TesterStub()
{
	try
	{
		_pServiceObject->testEvent -= Poco::delegate(this, &TesterStub::event__testEvent);
		_pServiceObject->testFilteredEvent -= Poco::delegate(this, &TesterStub::event__testFilteredEvent);
		_pServiceObject->testOneWayEvent -= Poco::delegate(this, &TesterStub::event__testOneWayEvent);
		_pServiceObject->testVoidEvent -= Poco::delegate(this, &TesterStub::event__testVoidEvent);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TesterStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void TesterStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TesterEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TesterStub::remoting__hasEvents() const
{
	return true;
}


void TesterStub::event__testEvent(std::string& data)
{
	testEvent(this, data);
}


void TesterStub::event__testFilteredEvent(const int& data)
{
	testFilteredEvent(this, data);
}


void TesterStub::event__testOneWayEvent(std::string& data)
{
	testOneWayEvent(this, data);
}


void TesterStub::event__testVoidEvent()
{
	testVoidEvent(this);
}


