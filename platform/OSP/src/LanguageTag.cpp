//
// LanguageTag.cpp
//
// Library: OSP
// Package: Util
// Module:  LanguageTag
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/LanguageTag.h"
#include "Poco/Environment.h"
#include <cctype>
#if defined(_WIN32)
#if defined(POCO_WIN32_UTF8)
#include "Poco/UnicodeConverter.h"
#endif
#include "Poco/UnWindows.h"
#endif


namespace Poco {
namespace OSP {


LanguageTag::LanguageTag()
{
	init();
}


LanguageTag::LanguageTag(const std::string& tag)
{
	init(tag);
}

	
LanguageTag::LanguageTag(const std::string& primaryTag, const std::string& subTags):
	_primaryTag(primaryTag),
	_subTags(subTags)
{
}


LanguageTag::~LanguageTag()
{
}


std::string LanguageTag::toString() const
{
	std::string result(_primaryTag);
	result += '-';
	result += _subTags;
	return result;
}


void LanguageTag::init()
{
#if defined(_WIN32)
#if defined(POCO_WIN32_UTF8)
	wchar_t buffer[8];
	int len = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SISO639LANGNAME, (LPWSTR) &buffer, sizeof(buffer)/sizeof(wchar_t));
	if (len > 0) Poco::UnicodeConverter::toUTF8(buffer, _primaryTag);
	len = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, (LPWSTR) &buffer, sizeof(buffer)/sizeof(wchar_t));
	if (len > 0) Poco::UnicodeConverter::toUTF8(buffer, _subTags);
#else
	char buffer[8];
	int len = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO639LANGNAME, (LPSTR) &buffer, sizeof(buffer));
	if (len > 0) _primaryTag.assign(buffer);
	len = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, (LPSTR) &buffer, sizeof(buffer));
	if (len > 0) _subTags.assign(buffer);
#endif
#endif

	if (_primaryTag.empty())
	{
		init(Poco::Environment::get("LANG", "en-US"));
	}
}


void LanguageTag::init(const std::string& tag)
{
	std::string::const_iterator it = tag.begin();
	std::string::const_iterator end = tag.end();
	
	while (it != end && *it != '-' && *it != '_')
	{
		_primaryTag += std::tolower(*it++);
	}
	if (it != end) ++it;
	while (it != end && *it != '-' && *it != '_' && *it != '.')
	{
		_subTags += std::toupper(*it++);
	}
}


} } // namespace Poco::OSP
