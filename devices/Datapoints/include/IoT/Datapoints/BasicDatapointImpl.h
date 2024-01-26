//
// BasicDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  BasicDatapointImpl
//
// Definition of the BasicDatapoint class template.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_BasicDatapointImpl_INCLUDED
#define IoT_Datapoints_BasicDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Devices/DeviceImpl.h"


namespace IoT {
namespace Datapoints {


template <class Super, class Sub>
class BasicDatapointImpl: public IoT::Devices::DeviceImpl<Super, Sub>
	/// This helper class adds support for properties via IoT::Devices::DeviceImpl 
	/// and adds a "customData" property to a datapoint.
{
public:
	BasicDatapointImpl():
		_customData(std::string())
	{
		using namespace std::string_literals;

		this->addProperty("customData"s, &BasicDatapointImpl::getCustomData, &BasicDatapointImpl::setCustomData);	
	}

protected:
	void makeInvalid(bool& valid)
	{
		if (valid)
		{
			valid = false;
			this->invalidated();
		}
	}

	template <typename T>
	void makeValid(bool& valid, const T& value)
	{
		if (!valid)
		{
			valid = true;
			this->validated(value);
		}
	}

private:
	Poco::Any getCustomData(const std::string&) const
	{
		// Note: access to _customData is already protected 
		// against concurrent access by DeviceImpl::_mutex 
		// through DeviceImpl::getPropertyXXX()/setPropertyXXX().
		return _customData;
	}

	void setCustomData(const std::string& name, const Poco::Any& value)
	{
		_customData = value;
	}

	Poco::Any _customData;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_BasicDatapointImpl_INCLUDED
