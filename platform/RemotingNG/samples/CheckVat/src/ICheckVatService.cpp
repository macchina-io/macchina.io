//
// ICheckVatService.cpp
//
// Package: Generated
// Module:  ICheckVatService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "CheckVat/ICheckVatService.h"


namespace CheckVat {


ICheckVatService::ICheckVatService():
	Poco::RefCountedObject()

{
}


ICheckVatService::~ICheckVatService()
{
}


const Poco::RemotingNG::Identifiable::TypeId& ICheckVatService::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("CheckVat.CheckVatService");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace CheckVat

