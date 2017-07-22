//
// AttributedObject.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Node
// Module:  Node
//
// Definition of the AttributedObject class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_AttributedObject_INCLUDED
#define IoT_Dataflow_Engine_AttributedObject_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <cstdlib>
#include <sstream>
#include <vector>
#include <map>


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API AttributedObject
	/// A AttributedObject can hold any number of attributes in 
	/// the form of name-value pairs.
{
public:
	typedef std::map<std::string, std::string> NameValueMap;

	AttributedObject();
		/// Creates an AttributedObject.

	AttributedObject(const AttributedObject& other);
		/// Creates an AttributedObject by copying the attributes from another one.
		
	AttributedObject& operator = (const AttributedObject& other);
		/// Assigns the attributes from another AttributedObject.

	virtual ~AttributedObject();
		/// Destroys the AttributedObject.
		
	void setAttribute(const std::string& name, const std::string& value);
		/// Adds or modifies the attribute with the given name.

	void setAttribute(const std::string& name, int value);
		/// Adds or modifies the attribute with the given name.

	void setAttribute(const std::string& name, double value);
		/// Adds or modifies the attribute with the given name.

	void setAttribute(const std::string& name, bool value);
		/// Adds or modifies the attribute with the given name.
		
	const std::string& getAttribute(const std::string& name) const;
		/// Returns the value of the attribute with the given name.
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		
	const std::string& getAttribute(const std::string& name, const std::string& deflt) const;
		/// Returns the value of the attribute with the given name,
		/// or the given default value if no such attribute
		/// exists.
		
	template <typename T>
	T getAttribute(const std::string& name) const
	{
		std::istringstream istr(getAttribute(name));
		T result;
		istr >> result;
		return result;
	}

	template <typename T>
	T getAttribute(const std::string& name, const T deflt) const
	{
		if (hasAttribute(name))
		{
			std::istringstream istr(getAttribute(name));
			T result;
			istr >> result;
			return result;
		}
		else return deflt;
	}
		
	int getIntAttribute(const std::string& name) const;
		/// Returns the value of the attribute with the given name
		/// as an integer.
		///
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		///
		/// Throws a Poco::SyntaxException if the attribute's value 
		/// is not a valid integer.

	int getIntAttribute(const std::string& name, const int deflt) const;
		/// Returns the value of the attribute with the given name
		/// as an integer, or the given default value if no such
		/// attribute exists.
		///
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		///
		/// Throws a Poco::SyntaxException if the attribute's value 
		/// is not a valid integer.

	double getDoubleAttribute(const std::string& name) const;
		/// Returns the value of the attribute with the given name
		/// as a double.
		///
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		///
		/// Throws a Poco::SyntaxException if the attribute's value 
		/// is not a valid double.

	double getDoubleAttribute(const std::string& name, const double deflt) const;
		/// Returns the value of the attribute with the given name
		/// as a double, or the given default value if no such
		/// attribute exists.
		///
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		///
		/// Throws a Poco::SyntaxException if the attribute's value 
		/// is not a valid double.

	bool getBoolAttribute(const std::string& name) const;
		/// Returns the value of the attribute with the given name
		/// as a boolean.
		///
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		///
		/// Throws a Poco::SyntaxException if the attribute's value 
		/// is not a valid boolean ("true" or "false", or any
		/// values supported by Poco::NumberParser::parseBool()).

	bool getBoolAttribute(const std::string& name, const bool deflt) const;
		/// Returns the value of the attribute with the given name
		/// as a bool, or the given default value if no such
		/// attribute exists.
		///
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		///
		/// Throws a Poco::SyntaxException if the attribute's value 
		/// is not a valid boolean ("true" or "false", or any
		/// values supported by Poco::NumberParser::parseBool()).

	bool hasAttribute(const std::string& name) const;
		/// Returns true iff an attribute with the given name exists.
		
	void removeAttribute(const std::string& name);
		/// Removes the attribute with the given name.
		///
		/// Does nothing if no attribute with the given name exists.
		
	std::size_t countAttributes() const;
		/// Returns the number of attributes.
		
	std::vector<std::string> enumerateAttributes() const;
		/// Returns a vector containing all attribute names.
		
	void clearAttributes();
		/// Removes all attributes.
	
private:
	NameValueMap _attributes;
};


//
// inlines
//
inline std::size_t AttributedObject::countAttributes() const
{
	return _attributes.size();
}


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_AttributedObject_INCLUDED
