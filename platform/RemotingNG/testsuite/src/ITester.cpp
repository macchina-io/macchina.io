//
// ITester.cpp
//
// Package: Generated
// Module:  ITester
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "ITester.h"


ITester::ITester():
	Poco::RefCountedObject(),
	testEvent(),
	testOneWayEvent(),
	testVoidEvent()
{
}


ITester::~ITester()
{
}


const Poco::RemotingNG::Identifiable::TypeId& ITester::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("Tester");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


