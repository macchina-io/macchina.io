//
// TwilioSMSEndpointProxy.cpp
//
// Package: Generated
// Module:  TwilioSMSEndpointProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#include "Twilio/TwilioSMSEndpointProxy.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Twilio/TwilioSMSResponseDeserializer.h"
#include "Twilio/TwilioSMSResponseSerializer.h"


namespace Twilio {


TwilioSMSEndpointProxy::TwilioSMSEndpointProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid):
	Twilio::ITwilioSMSEndpoint(),
	Poco::RemotingNG::Proxy(oid),
	_postRet()
{
}


TwilioSMSEndpointProxy::~TwilioSMSEndpointProxy()
{
}


Twilio::TwilioSMSResponse TwilioSMSEndpointProxy::post(const std::string& accountSID, const std::string& from, const std::string& to, const std::string& body)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"post","accountSID","From","To","Body"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_PATH, "/2010-04-01/Accounts/{accountSID}/SMS/Messages.json");
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION, "path");
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], accountSID, remoting__ser);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION, "form");
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], from, remoting__ser);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION, "form");
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], to, remoting__ser);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION, "form");
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], body, remoting__ser);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_PATH);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("postReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Twilio::TwilioSMSResponse >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _postRet);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__trans.endRequest();
	return _postRet;
}


const std::string TwilioSMSEndpointProxy::DEFAULT_NS("");
} // namespace Twilio

