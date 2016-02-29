//
// LanguageTag.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/LanguageTag.h#1 $
//
// Library: OSP
// Package: Util
// Module:  LanguageTag
//
// Definition of the LanguageTag class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_LanguageTag_INCLUDED
#define OSP_LanguageTag_INCLUDED


#include "Poco/OSP/OSP.h"


namespace Poco {
namespace OSP {


class OSP_API LanguageTag
	/// This class implements a RFC 1766 language tag.
	///
	/// A language tag describes a language and consists
	/// of a primary tag and one or more subtags.
	/// Usually, the primary tag conforms to an ISO 639
	/// language code and the first subtag conforms to an
	/// ISO 3166 country code. For the details, please
	/// refer to RFC 1766.
	///
	/// In a string representation, primary and subtags
	/// are separated by '-', e.g., "en-US" or "de-AT".
{
public:
	LanguageTag();
		/// Creates a LanguageTag for the system's default language.
		///
		/// On Windows platform, the system's locale information 
		/// is used. On Unix platform, the value of the environment
		/// variable LANG is used. If LANG is not defined, the default
		/// "en-US" is used.
		
	LanguageTag(const std::string& tag);
		/// Creates the LanguageTag from the tag given in the string argument.
		
	LanguageTag(const std::string& primaryTag, const std::string& subTags);
		/// Creates the LanguageTag from the given primary and sub tags.

	~LanguageTag();
		/// Destroys the LanguageTag.

	const std::string& primaryTag() const;
		/// Returns the primary tag.
		
	const std::string& subTags() const;
		/// Returns all sub tags, delimited by a '-'.
		
	std::string toString() const;
		/// Returns a string representation of the language tag.

private:
	void init();
	void init(const std::string& tag);

	std::string _primaryTag;
	std::string _subTags;
};


//
// inlines
//
inline const std::string& LanguageTag::primaryTag() const
{
	return _primaryTag;
}


inline const std::string& LanguageTag::subTags() const
{
	return _subTags;
}


} } // namespace Poco::OSP


#endif // OSP_LanguageTag_INCLUDED
