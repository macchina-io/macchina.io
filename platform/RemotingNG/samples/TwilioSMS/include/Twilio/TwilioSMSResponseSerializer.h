//
// TwilioSMSResponseSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeSerializer_Twilio_TwilioSMSResponse_INCLUDED
#define TypeSerializer_Twilio_TwilioSMSResponse_INCLUDED


#include "Poco/RemotingNG/TypeSerializer.h"
#include "Twilio/TwilioSMSEndpoint.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Twilio::TwilioSMSResponse>
{
public:
	static void serialize(const std::string& name, const Twilio::TwilioSMSResponse& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Twilio::TwilioSMSResponse& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"account_sid","api_version","body","date_created","date_sent","date_updated","direction","from","num_segments","price","price_unit","sid","status","to","uri",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.accountSID, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.apiVersion, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.body, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], value.dateCreated, ser);
		TypeSerializer<Poco::Nullable < std::string > >::serialize(REMOTING__NAMES[4], value.dateSent, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[5], value.dateUpdated, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[6], value.direction, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[7], value.from, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[8], value.num_segments, ser);
		TypeSerializer<Poco::Nullable < std::string > >::serialize(REMOTING__NAMES[9], value.price, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[10], value.price_unit, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[11], value.sid, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[12], value.status, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[13], value.to, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[14], value.uri, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Twilio_TwilioSMSResponse_INCLUDED

