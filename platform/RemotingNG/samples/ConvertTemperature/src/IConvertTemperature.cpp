//
// IConvertTemperature.cpp
//
// Package: Generated
// Module:  IConvertTemperature
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "WebServiceX/IConvertTemperature.h"


namespace WebServiceX {


IConvertTemperature::IConvertTemperature():
	Poco::RefCountedObject()

{
}


IConvertTemperature::~IConvertTemperature()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IConvertTemperature::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("WebServiceX.ConvertTemperature");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace WebServiceX

