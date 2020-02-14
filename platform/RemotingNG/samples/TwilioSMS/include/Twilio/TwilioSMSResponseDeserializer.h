//
// TwilioSMSResponseDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeDeserializer_Twilio_TwilioSMSResponse_INCLUDED
#define TypeDeserializer_Twilio_TwilioSMSResponse_INCLUDED


#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Twilio/TwilioSMSEndpoint.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Twilio::TwilioSMSResponse>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Twilio::TwilioSMSResponse& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Twilio::TwilioSMSResponse& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"account_sid","api_version","body","date_created","date_sent","date_updated","direction","from","num_segments","price","price_unit","sid","status","to","uri"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.accountSID);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.apiVersion);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.body);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.dateCreated);
		TypeDeserializer<Poco::Nullable < std::string > >::deserialize(REMOTING__NAMES[4], true, deser, value.dateSent);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[5], true, deser, value.dateUpdated);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[6], true, deser, value.direction);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[7], true, deser, value.from);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[8], true, deser, value.num_segments);
		TypeDeserializer<Poco::Nullable < std::string > >::deserialize(REMOTING__NAMES[9], true, deser, value.price);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[10], true, deser, value.price_unit);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[11], true, deser, value.sid);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[12], true, deser, value.status);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[13], true, deser, value.to);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[14], true, deser, value.uri);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Twilio_TwilioSMSResponse_INCLUDED

