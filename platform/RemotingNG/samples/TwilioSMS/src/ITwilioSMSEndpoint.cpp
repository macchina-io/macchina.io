//
// ITwilioSMSEndpoint.cpp
//
// Package: Generated
// Module:  ITwilioSMSEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "Twilio/ITwilioSMSEndpoint.h"


namespace Twilio {


ITwilioSMSEndpoint::ITwilioSMSEndpoint():
	Poco::RefCountedObject()

{
}


ITwilioSMSEndpoint::~ITwilioSMSEndpoint()
{
}


const Poco::RemotingNG::Identifiable::TypeId& ITwilioSMSEndpoint::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("Twilio.TwilioSMSEndpoint");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Twilio

