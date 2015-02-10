//
// LatLonDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_Devices_LatLon_INCLUDED
#define TypeDeserializer_IoT_Devices_LatLon_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Devices::LatLon>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Devices::LatLon& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::Devices::LatLon& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"latitude","longitude"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<double >::deserialize(REMOTING__NAMES[0], true, deser, value.latitude);
		TypeDeserializer<double >::deserialize(REMOTING__NAMES[1], true, deser, value.longitude);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Devices_LatLon_INCLUDED

