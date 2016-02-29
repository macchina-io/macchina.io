//
// TypeSerializer.h
//
// $Id: //poco/1.7/RemotingNG/include/Poco/RemotingNG/TypeSerializer.h#1 $
//
// Library: RemotingNG
// Package: Serialization
// Module:  TypeSerializer
//
// Definition of the TypeSerializer class template and its specializations.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_TypeSerializer_INCLUDED
#define RemotingNG_TypeSerializer_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/Optional.h"
#include "Poco/Nullable.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/URI.h"
#include "Poco/UUID.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include <vector>
#include <list>
#include <set>


namespace Poco {
namespace RemotingNG {


template <typename T>
class TypeSerializer
	/// TypeSerializer is used to serialize the content of a variable
	/// for transportation over the network.
	///
	/// The default TypeSerializer template simply forwards serialize()
	/// calls to a Serializer. This means that serializaation using the
	/// default template only works for types directly supported
	/// by Serializer.
	///
	/// Serialization of complex types can be done by providing
	/// specializations of the TypeSerializer class template.
{
public:
	static void serialize(const std::string& name, const T& value, Serializer& ser)
	{
		ser.serialize(name, value);
	}
	
private:
	TypeSerializer();
	~TypeSerializer();
	
	TypeSerializer(const TypeSerializer&);
	TypeSerializer& operator = (const TypeSerializer&);
};


template <typename T>
class TypeSerializer<std::vector<T> >
{
public:
	static void serialize(const std::string& name, const std::vector<T>& value, Serializer& ser)
	{
		ser.serializeSequenceBegin(name, static_cast<Poco::UInt32>(value.size()));
		serializeImpl(name, value, ser);
		ser.serializeSequenceEnd(name);
	}

	static void serializeImpl(const std::string& name, const std::vector<T>& value, Serializer& ser)
	{
		typename std::vector<T>::const_iterator it = value.begin();
		typename std::vector<T>::const_iterator itEnd = value.end();
		for (; it != itEnd; ++it)
		{
			TypeSerializer<T>::serialize(name, *it, ser);
		}
	}
};


template <typename T>
class TypeSerializer<std::list<T> >
{
public:
	static void serialize(const std::string& name, const std::list<T>& value, Serializer& ser)
	{
		ser.serializeSequenceBegin(name, static_cast<Poco::UInt32>(value.size()));
		serializeImpl(name, value, ser);
		ser.serializeSequenceEnd(name);
	}

	static void serializeImpl(const std::string& name, const std::list<T>& value, Serializer& ser)
	{
		typename std::list<T>::const_iterator it = value.begin();
		typename std::list<T>::const_iterator itEnd = value.end();
		for (; it != itEnd; ++it)
		{
			TypeSerializer<T>::serialize(name, *it, ser);
		}
	}
};


template <typename T>
class TypeSerializer<std::set<T> >
{
public:
	static void serialize(const std::string& name, const std::set<T>& value, Serializer& ser)
	{
		ser.serializeSequenceBegin(name, static_cast<Poco::UInt32>(value.size()));
		serializeImpl(name, value, ser);
		ser.serializeSequenceEnd(name);
	}

	static void serializeImpl(const std::string& name, const std::set<T>& value, Serializer& ser)
	{
		typename std::set<T>::const_iterator it = value.begin();
		typename std::set<T>::const_iterator itEnd = value.end();
		for (; it != itEnd; ++it)
		{
			TypeSerializer<T>::serialize(name, *it, ser);
		}
	}
};


template <typename T>
class TypeSerializer<std::multiset<T> >
{
public:
	static void serialize(const std::string& name, const std::multiset<T>& value, Serializer& ser)
	{
		ser.serializeSequenceBegin(name, static_cast<Poco::UInt32>(value.size()));
		serializeImpl(name, value, ser);
		ser.serializeSequenceEnd(name);
	}

	static void serializeImpl(const std::string& name, const std::multiset<T>& value, Serializer& ser)
	{
		typename std::multiset<T>::const_iterator it = value.begin();
		typename std::multiset<T>::const_iterator itEnd = value.end();
		for (; it != itEnd; ++it)
		{
			TypeSerializer<T>::serialize(name, *it, ser);
		}
	}
};


template <typename T>
class TypeSerializer<Poco::Nullable<T> >
{
public:
	static void serialize(const std::string& name, const Poco::Nullable<T>& value, Serializer& ser)
	{
		ser.serializeNullableBegin(name, value.isNull());
		if (!value.isNull())
		{
			TypeSerializer<T>::serialize(name, value.value(), ser);
		}
		ser.serializeNullableEnd(name);
	}
};


template <typename T>
class TypeSerializer<Poco::Optional<T> >
{
public:
	static void serialize(const std::string& name, const Poco::Optional<T>& value, Serializer& ser)
	{
		ser.serializeOptionalBegin(name, value.isSpecified());
		if (value.isSpecified())
		{
			TypeSerializer<T>::serialize(name, value.value(), ser);
		}
		ser.serializeOptionalEnd(name);
	}
};


template <typename T>
class TypeSerializer<Poco::AutoPtr<T> >
{
public:
	static void serialize(const std::string& name, Poco::AutoPtr<T> value, Serializer& ser)
	{
		if (value)
		{
			ser.serializeNullableBegin(name, false);
			TypeSerializer<T>::serialize(name, *value, ser);
			ser.serializeNullableEnd(name);
		}
		else
		{
			ser.serializeNullableBegin(name, true);
			ser.serializeNullableEnd(name);
		}
	}
};


template <typename T>
class TypeSerializer<Poco::SharedPtr<T> > 
{
public:
	static void serialize(const std::string& name, Poco::SharedPtr<T> value, Serializer& ser)
	{
		if (value)
		{
			ser.serializeNullableBegin(name, false);
			TypeSerializer<T>::serialize(name, *value, ser);
			ser.serializeNullableEnd(name);
		}
		else
		{
			ser.serializeNullableBegin(name, true);
			ser.serializeNullableEnd(name);
		}
	}
};


template <>
class TypeSerializer<Poco::URI>
{
public:
	static void serialize(const std::string& name, const Poco::URI& value, Serializer& ser)
	{
		std::string tmp(value.toString());
		ser.serialize(name, tmp);
	}
};


template <>
class TypeSerializer<Poco::UUID>
{
public:
	static void serialize(const std::string& name, const Poco::UUID& value, Serializer& ser)
	{
		std::string tmp(value.toString());
		ser.serialize(name, tmp);
	}
};


template <>
class TypeSerializer<std::vector<char> >
{
public:
	static void serialize(const std::string& name, const std::vector<char>& value, Serializer& ser)
	{
		ser.serialize(name, value);
	}
};


template <>
class TypeSerializer<Poco::DateTime>
{
public:
	static void serialize(const std::string& name, const Poco::DateTime& value, Serializer& ser)
	{
		std::string dt(Poco::DateTimeFormatter::format(value, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
		TypeSerializer<std::string>::serialize(name, dt, ser);
	}
};


template <>
class TypeSerializer<Poco::LocalDateTime>
{
public:
	static void serialize(const std::string& name, const Poco::LocalDateTime& value, Serializer& ser)
	{
		std::string tmp (Poco::DateTimeFormatter::format(value, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
		TypeSerializer<std::string>::serialize(name, tmp, ser);
	}
};


template <>
class TypeSerializer<Poco::Timestamp>
{
public:
	static void serialize(const std::string& name, const Poco::Timestamp& value, Serializer& ser)
	{
		std::string tmp (Poco::DateTimeFormatter::format(value, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
		TypeSerializer<std::string>::serialize(name, tmp, ser);
	}
};


template <>
class TypeSerializer<Poco::Timespan>
{
public:
	static void serialize(const std::string& name, const Poco::Timespan& value, Serializer& ser)
	{
		Poco::Timespan::TimeDiff ms = value.totalMicroseconds();
		TypeSerializer<Poco::Timespan::TimeDiff>::serialize(name, ms, ser);
	}
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_TypeSerializer_INCLUDED
