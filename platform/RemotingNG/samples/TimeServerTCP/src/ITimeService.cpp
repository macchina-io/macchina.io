//
// ITimeService.cpp
//
// Package: Generated
// Module:  ITimeService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2015, Applied Informatics Software Engineering GmbH.
//


#include "ITimeService.h"


namespace Services {


ITimeService::ITimeService():
	Poco::RefCountedObject(),
	wakeUp()
{
}


ITimeService::~ITimeService()
{
}


const Poco::RemotingNG::Identifiable::TypeId& ITimeService::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("TimeService");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Services

