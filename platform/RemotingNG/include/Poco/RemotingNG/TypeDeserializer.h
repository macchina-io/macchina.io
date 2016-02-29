//
// TypeDeserializer.h
//
// $Id: //poco/1.7/RemotingNG/include/Poco/RemotingNG/TypeDeserializer.h#1 $
//
// Library: RemotingNG
// Package: Serialization
// Module:  TypeDeserializer
//
// Definition of the TypeDeserializer class template and its specializations.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_TypeDeserializer_INCLUDED
#define RemotingNG_TypeDeserializer_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/Optional.h"
#include "Poco/Nullable.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "Poco/UUID.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include <vector>
#include <list>
#include <set>


namespace Poco {
namespace RemotingNG {


template <typename T>
class TypeDeserializer
	/// TypeDeserializer is used to deserialize the content of a variable
	/// for transportation over the network.
	///
	/// The default TypeDeserializer template simply forwards deserialize()
	/// calls to a Deserializer. This means that deserializaation using the
	/// default template only works for types directly supported
	/// by Deserializer.
	///
	/// Serialization of complex types can be done by providing
	/// specializations of the TypeDeserializer class template.
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, T& value)
	{
		return deser.deserialize(name, isMandatory, value);
	}

private:
	TypeDeserializer();
	~TypeDeserializer();

	TypeDeserializer(const TypeDeserializer&);
	TypeDeserializer& operator = (const TypeDeserializer&);
};


template <typename T>
class TypeDeserializer<std::vector<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, std::vector<T>& value)
	{
		Poco::UInt32 sizeHint;
		if (deser.deserializeSequenceBegin(name, isMandatory, sizeHint))
		{
			if (sizeHint > 0) value.reserve(sizeHint);
			deserializeImpl(name, false, deser, value);
			deser.deserializeSequenceEnd(name);
			return true;
		}
		else return false;
	}

	static void deserializeImpl(const std::string& name, bool isMandatory, Deserializer& deser, std::vector<T>& value)
	{
		value.clear();
		bool found = true;
		do
		{
			T elem; // recreate elem with default values in EACH iteration -> deserialize can return true even when no data was set!
			found = TypeDeserializer<T>::deserialize(name, isMandatory, deser, elem);
			if (found)
			{
				value.push_back(elem);
			}
		}
		while (found);
	}
};


template <typename T>
class TypeDeserializer<std::list<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, std::list<T>& value)
	{
		Poco::UInt32 sizeHint;
		if (deser.deserializeSequenceBegin(name, isMandatory, sizeHint))
		{
			deserializeImpl(name, false, deser, value);
			deser.deserializeSequenceEnd(name);
			return true;
		}
		else return false;
	}

	static void deserializeImpl(const std::string& name, bool isMandatory, Deserializer& deser, std::list<T>& value)
	{
		value.clear();
		bool found = true;
		do
		{
			T elem; // recreate elem with default values in EACH iteration -> deserialize can return true even when no data was set!
			found = TypeDeserializer<T>::deserialize(name, isMandatory, deser, elem);
			if (found)
			{
				value.push_back(elem);
			}
		}
		while (found);
	}
};


template <typename T>
class TypeDeserializer<std::set<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, std::set<T>& value)
	{
		Poco::UInt32 sizeHint;
		if (deser.deserializeSequenceBegin(name, isMandatory, sizeHint))
		{
			deserializeImpl(name, false, deser, value);
			deser.deserializeSequenceEnd(name);
			return true;
		}
		else return false;
	}

	static void deserializeImpl(const std::string& name, bool isMandatory, Deserializer& deser, std::set<T>& value)
	{
		value.clear();
		bool found = true;
		do
		{
			T elem; // recreate elem with default values in EACH iteration -> deserialize can return true even when no data was set!
			found = TypeDeserializer<T>::deserialize(name, isMandatory, deser, elem);
			if (found)
			{
				value.insert(elem);
			}
		}
		while (found);
	}
};


template <typename T>
class TypeDeserializer<std::multiset<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, std::multiset<T>& value)
	{
		Poco::UInt32 sizeHint;
		if (deser.deserializeSequenceBegin(name, isMandatory, sizeHint))
		{
			deserializeImpl(name, false, deser, value);
			deser.deserializeSequenceEnd(name);
			return true;
		}
		else return false;
	}

	static void deserializeImpl(const std::string& name, bool isMandatory, Deserializer& deser, std::multiset<T>& value)
	{
		value.clear();
		bool found = true;
		do
		{
			T elem; // recreate elem with default values in EACH iteration -> deserialize can return true even when no data was set!
			found = TypeDeserializer<T>::deserialize(name, isMandatory, deser, elem);
			if (found)
			{
				value.insert(elem);
			}
		}
		while (found);
	}
};


template <typename T>
class TypeDeserializer<Poco::Nullable<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::Nullable<T>& value)
	{
		bool isNull;
		if (deser.deserializeNullableBegin(name, isMandatory, isNull))
		{
			if (!isNull)
			{
				deserializeImpl(name, false, deser, value);
				deser.deserializeNullableEnd(name);
			}
			else value.clear();
			return true;
		}
		value.clear();
		return false;
	}

	static void deserializeImpl(const std::string& name, bool isMandatory, Deserializer& deser, Poco::Nullable<T>& value)
	{
		T temp; 
		if (TypeDeserializer<T>::deserialize(name, isMandatory, deser, temp))
			value = temp;
		else
			value.clear();
	}
};


template <typename T>
class TypeDeserializer<Poco::Optional<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::Optional<T>& value)
	{
		bool isSpecified;
		if (deser.deserializeOptionalBegin(name, isMandatory, isSpecified))
		{
			if (isSpecified)
			{
				deserializeImpl(name, false, deser, value);
				deser.deserializeOptionalEnd(name);
			}
			else value.clear();
			return true;
		}
		value.clear();
		return false;
	}

	static void deserializeImpl(const std::string& name, bool isMandatory, Deserializer& deser, Poco::Optional<T>& value)
	{
		T temp; 
		if (TypeDeserializer<T>::deserialize(name, isMandatory, deser, temp))
			value = temp;
		else
			value.clear();
	}
};


template <typename T>
class TypeDeserializer<Poco::AutoPtr<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::AutoPtr<T>& value)
	{
		bool isNull;
		bool found = deser.deserializeNullableBegin(name, isMandatory, isNull);
		if (found && !isNull)
		{
			Poco::AutoPtr<T> tmp(new T());
			found = TypeDeserializer<T>::deserialize(name, isMandatory, deser, *tmp.get());
			if (found)
			{
				value = tmp;
				deser.deserializeNullableEnd(name);
				return true;
			}
		}
		value = 0;
		return found;
	}
};


template <typename T>
class TypeDeserializer<Poco::SharedPtr<T> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::SharedPtr<T>& value)
	{
		bool isNull;
		bool found = deser.deserializeNullableBegin(name, isMandatory, isNull);
		if (found && !isNull)
		{
			Poco::SharedPtr<T> tmp(new T());
			found = TypeDeserializer<T> ::deserialize(name, isMandatory, deser, *tmp.get());
			if (found)
			{
				value = tmp;
				deser.deserializeNullableEnd(name);
				return true;
			}
		}
		value = 0;
		return found;
	}
};


template <>
class TypeDeserializer<Poco::URI>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::URI& value)
	{
		std::string uriStr;
		bool found = deser.deserialize(name, isMandatory, uriStr);
		if (found)
			value = uriStr;
		else
			value.clear();
		return found;
	}
};


template <>
class TypeDeserializer<Poco::UUID>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::UUID& value)
	{
		std::string uuidStr;
		bool found = deser.deserialize(name, isMandatory, uuidStr);
		if (found)
			value.parse(uuidStr);
		else
			value = Poco::UUID();
		return found;
	}
};


template <>
class TypeDeserializer<std::vector<char> >
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, std::vector<char>& value)
	{
		return deser.deserialize(name, isMandatory, value);
	}
};


template <>
class TypeDeserializer<Poco::DateTime>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::DateTime& value)
	{
		std::string timeStr;
		bool found = TypeDeserializer<std::string>::deserialize(name, isMandatory, deser, timeStr);
		if (found)
		{
			int tzd = 0; 
			Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FRAC_FORMAT, timeStr, value, tzd);
			value.makeUTC(tzd);
		}
		return found;
	}
};


template <>
class TypeDeserializer<Poco::LocalDateTime>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::LocalDateTime& value)
	{
		std::string timeStr;
		bool found = TypeDeserializer<std::string>::deserialize(name, isMandatory, deser, timeStr);
		if (found)
		{
			int tzd = 0;
			Poco::DateTime dt;
			Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FRAC_FORMAT, timeStr, dt, tzd);
			value = Poco::LocalDateTime(tzd, dt, false);
		}
		return found;
	}
};


template <>
class TypeDeserializer<Poco::Timestamp>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::Timestamp& value)
	{
		Poco::DateTime dt;
		bool found = TypeDeserializer<Poco::DateTime>::deserialize(name, isMandatory, deser, dt);
		if (found)
		{
			value = dt.timestamp();
		}
		return found;
	}
};


template <>
class TypeDeserializer<Poco::Timespan>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Poco::Timespan& value)
			/// Deserialize for complex data types.
	{
		Poco::Timespan::TimeDiff diff;
		bool found = TypeDeserializer<Poco::Timespan::TimeDiff>::deserialize(name, isMandatory, deser, diff);
		if (found)
		{
			value = Poco::Timespan(diff);
		}
		return found;
	}
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_TypeDeserializer_INCLUDED
