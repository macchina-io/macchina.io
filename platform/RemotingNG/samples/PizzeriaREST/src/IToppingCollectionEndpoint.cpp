//
// IToppingCollectionEndpoint.cpp
//
// Package: Generated
// Module:  IToppingCollectionEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
//


#include "Pizzeria/IToppingCollectionEndpoint.h"


namespace Pizzeria {


IToppingCollectionEndpoint::IToppingCollectionEndpoint():
	Poco::RefCountedObject()

{
}


IToppingCollectionEndpoint::~IToppingCollectionEndpoint()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IToppingCollectionEndpoint::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("Pizzeria.ToppingCollectionEndpoint");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Pizzeria

