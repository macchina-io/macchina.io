//
// IOrderEndpoint.cpp
//
// Package: Generated
// Module:  IOrderEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
//


#include "Pizzeria/IOrderEndpoint.h"


namespace Pizzeria {


IOrderEndpoint::IOrderEndpoint():
	Poco::RefCountedObject()

{
}


IOrderEndpoint::~IOrderEndpoint()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IOrderEndpoint::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("Pizzeria.OrderEndpoint");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Pizzeria

