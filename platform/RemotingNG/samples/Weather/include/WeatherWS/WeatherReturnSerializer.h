//
// WeatherReturnSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeSerializer_WeatherWS_WeatherReturn_INCLUDED
#define TypeSerializer_WeatherWS_WeatherReturn_INCLUDED


#include "Poco/RemotingNG/TypeSerializer.h"
#include "WeatherWS/WeatherReturn.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<WeatherWS::WeatherReturn>
{
public:
	static void serialize(const std::string& name, const WeatherWS::WeatherReturn& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMESPACE);
		static const std::string REMOTING__NAMESPACE("http://ws.cdyne.com/WeatherWS/");
		remoting__staticInitEnd(REMOTING__NAMESPACE);
		ser.registerNamespace(REMOTING__NAMESPACE);
		ser.serializeStructBegin(name);
		ser.pushProperty(SerializerBase::PROP_NAMESPACE, REMOTING__NAMESPACE);
		serializeImpl(value, ser);
		ser.popProperty(SerializerBase::PROP_NAMESPACE);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const WeatherWS::WeatherReturn& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"Success","ResponseText","State","City","WeatherStationCity","WeatherID","Description","Temperature","RelativeHumidity","Wind","Pressure","Visibility","WindChill","Remarks",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[0], value.getSuccess(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[1], value.getResponseText(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[2], value.getState(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[3], value.getCity(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[4], value.getWeatherStationCity(), ser);
		TypeSerializer<Poco::Int16 >::serialize(REMOTING__NAMES[5], value.getWeatherID(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[6], value.getDescription(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[7], value.getTemperature(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[8], value.getRelativeHumidity(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[9], value.getWind(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[10], value.getPressure(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[11], value.getVisibility(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[12], value.getWindChill(), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[13], value.getRemarks(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_WeatherWS_WeatherReturn_INCLUDED

