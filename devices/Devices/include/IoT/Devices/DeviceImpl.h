//
// DeviceImpl.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/DeviceImpl.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  DeviceImpl
//
// Definition of the DeviceImpl helper class template.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceImpl_INCLUDED
#define IoT_Devices_DeviceImpl_INCLUDED


#include "IoT/Devices/Device.h"
#include "IoT/Devices/DeviceException.h"
#include "Poco/Mutex.h"
#include "Poco/Any.h"
#include <map>


namespace IoT {
namespace Devices {


template <class Super, class Sub>
class DeviceImpl: public Super
	/// A helper class for implementing device features and properties.
{
public:
	typedef void (Sub::*FeatureSetter)(const std::string&, bool);
		/// The setter method for a feature.
		
	typedef bool (Sub::*FeatureGetter)(const std::string&) const;
		/// The getter method for a feature.
		
	typedef void (Sub::*PropertySetter)(const std::string&, const Poco::Any&);
		/// The setter method for a property.
		
	typedef Poco::Any (Sub::*PropertyGetter)(const std::string&) const;
		/// The getter method for a property.

	void setPropertyString(const std::string& name, const std::string& value)
	{
		setProperty(name, value);
	}
	
	std::string getPropertyString(const std::string& name) const
	{
		return Poco::AnyCast<std::string>(getProperty(name));
	}

	void setPropertyInt(const std::string& name, int value)
	{
		setProperty(name, value);
	}
	
	int getPropertyInt(const std::string& name) const
	{
		return Poco::AnyCast<int>(getProperty(name));
	}

	void setPropertyDouble(const std::string& name, double value)
	{
		setProperty(name, value);
	}
	
	double getPropertyDouble(const std::string& name) const
	{
		return Poco::AnyCast<double>(getProperty(name));
	}

	void setPropertyBool(const std::string& name, bool value)
	{
		setProperty(name, value);
	}
	
	bool getPropertyBool(const std::string& name) const
	{
		return Poco::AnyCast<bool>(getProperty(name));
	}

	void setProperty(const std::string& name, const Poco::Any& value)
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		typename PropertyMap::const_iterator it = _properties.find(name);
		if (it != _properties.end())
		{
			if (it->second.setter)
				(static_cast<Sub*>(this)->*it->second.setter)(name, value);
			else
				throw NotWritableException(name);
		}
		else throw NotSupportedException(name);
	}
		
	Poco::Any getProperty(const std::string& name) const
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		typename PropertyMap::const_iterator it = _properties.find(name);
		if (it != _properties.end())
		{
			if (it->second.getter)
				return (static_cast<const Sub*>(this)->*it->second.getter)(name);
			else
				throw NotReadableException(name);
		}
		else throw NotSupportedException(name);
	}
		
	bool hasProperty(const std::string& name) const
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		typename PropertyMap::const_iterator it = _properties.find(name);
		return it != _properties.end();
	}
			
	void setFeature(const std::string& name, bool enable)
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		typename FeatureMap::const_iterator it = _features.find(name);
		if (it != _features.end())
		{
			if (it->second.setter)
				(static_cast<Sub*>(this)->*it->second.setter)(name, enable);
			else
				throw NotWritableException(name);
		}
		else throw NotSupportedException(name);
	}
	
	bool getFeature(const std::string& name) const
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		typename FeatureMap::const_iterator it = _features.find(name);
		if (it != _features.end())
		{
			if (it->second.getter)
				return (static_cast<const Sub*>(this)->*it->second.getter)(name);
			else
				throw NotReadableException(name);
		}
		else throw NotSupportedException(name);
	}
	
	bool hasFeature(const std::string& name) const
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		typename FeatureMap::const_iterator it = _features.find(name);
		return it != _features.end();
	}
	
protected:
	void addFeature(const std::string& name, FeatureGetter getter, FeatureSetter setter = 0)
		/// Adds a feature to the map of supported features.
		///
		/// The setter or getter can be null, in case setting or getting a feature
		/// is not supported.
	{
		Feature feature;
		feature.getter = getter;
		feature.setter = setter;
		_features[name] = feature;
	}
		
	void addProperty(const std::string& name, PropertyGetter getter, PropertySetter setter = 0)
		/// Adds a property to the map of supported properties.
		///
		/// The setter or getter can be null, in case setting or getting a property
		/// is not supported.
	{
		Property property;
		property.getter = getter;
		property.setter = setter;
		_properties[name] = property;
	}

	struct Feature
	{
		FeatureSetter setter;
		FeatureGetter getter;
	};
	
	struct Property
	{
		PropertySetter setter;
		PropertyGetter getter;
	};
	
	typedef std::map<std::string, Feature>  FeatureMap;
	typedef std::map<std::string, Property> PropertyMap;
	
	FeatureMap  _features;
	PropertyMap _properties;
	mutable Poco::Mutex _mutex;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_DeviceImpl_INCLUDED
