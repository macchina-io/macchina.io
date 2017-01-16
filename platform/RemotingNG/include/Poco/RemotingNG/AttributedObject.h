//
// AttributedObject.h
//
// $Id: //poco/1.7/RemotingNG/include/Poco/RemotingNG/AttributedObject.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  AttributedObject
//
// Definition of the AttributedObject class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_AttributedObject_INCLUDED
#define RemotingNG_AttributedObject_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace RemotingNG {


class RemotingNG_API AttributedObject
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
		
	const std::string& getAttribute(const std::string& name) const;
		/// Returns the value of the attribute with the given name.
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		
	const std::string& getAttribute(const std::string& name, const std::string& deflt) const;
		/// Returns the value of the attribute with the given name,
		/// or the given default value if no such attribute
		/// exists.
	
	bool hasAttribute(const std::string& name) const;
		/// Returns true iff an attribute with the given name exists.
		
private:
	NameValueMap _attributes;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_AttributedObject_INCLUDED
