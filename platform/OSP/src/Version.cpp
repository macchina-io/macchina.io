//
// Version.cpp
//
// Library: OSP
// Package: Core
// Module:  Version
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Version.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"
#include <algorithm>
#include <cctype>


using Poco::NumberFormatter;


namespace Poco {
namespace OSP {


Version::Version():
	_major(0),
	_minor(0),
	_revision(0)
{
}


Version::Version(const Version& version):
	_major(version._major),
	_minor(version._minor),
	_revision(version._revision),
	_designation(version._designation)
{
}

	
Version::Version(int major, int minor, int revision):
	_major(major),
	_minor(minor),
	_revision(revision)
{
}

	
Version::Version(int major, int minor, int revision, const std::string& designation):
	_major(major),
	_minor(minor),
	_revision(revision),
	_designation(designation)
{
}


Version::Version(const std::string& version)
{
	parse(version);
}


Version::~Version()
{
}


Version& Version::operator = (const Version& version)
{
	Version tmp(version);
	swap(tmp);
	return *this;
}


Version& Version::operator = (const std::string& version)
{
	parse(version);
	return *this;
}


void Version::swap(Version& version)
{
	using std::swap;
	swap(_major, version._major);
	swap(_minor, version._minor);
	swap(_revision, version._revision);
	swap(_designation, version._designation);
}

	
std::string Version::toString() const
{
	std::string result;
	result += NumberFormatter::format(_major);
	result += '.';
	result += NumberFormatter::format(_minor);
	result += '.';
	result += NumberFormatter::format(_revision);
	if (!_designation.empty())
	{
		result += '-';
		result += _designation;
	}
	return result;
}

	
void Version::parse(const std::string& str)
{
	int maj(0);
	int min(0);
	int rev(0);
	std::string designation;
	
	std::string::const_iterator it(str.begin());
	std::string::const_iterator end(str.end());
	if (std::isdigit(*it))
	{
		while (it != end && std::isdigit(*it))
			maj = 10*maj + *it++ - '0';

		if (it != end && *it == '.')
		{
			++it;
			while (it != end && std::isdigit(*it))
				min = 10*min + *it++ - '0';

			if (it != end && *it == '.')
			{
				++it;
				while (it != end && std::isdigit(*it))
					rev = 10*rev + *it++ - '0';

				if (it != end && *it == '-')
				{
					++it;
					while (it != end)
						designation += *it++;
				}
			}
		}
	}
	if (it == end) 
	{
		_major = maj;
		_minor = min;
		_revision = rev;
		std::swap(_designation, designation);
	}
	else throw Poco::SyntaxException("Not a valid version number", str);
}


bool Version::operator == (const Version& version) const
{
	return _major    == version._major
	    && _minor    == version._minor
	    && _revision == version._revision;
}


bool Version::operator != (const Version& version) const
{
	return _major    != version._major
	    || _minor    != version._minor
	    || _revision != version._revision;

}


bool Version::operator <  (const Version& version) const
{
	if (_major < version._major)
	{
		return true;
	}
	else if (_major == version._major)
	{
		if (_minor < version._minor)
			return true;
		else if (_minor == version._minor)
			return _revision < version._revision;
	}
	return false;
}


bool Version::operator <= (const Version& version) const
{
	if (_major < version._major)
	{
		return true;
	}
	else if (_major == version._major)
	{
		if (_minor < version._minor)
			return true;
		else if (_minor == version._minor)
			return _revision <= version._revision;
	}
	return false;
}


bool Version::operator >  (const Version& version) const
{
	if (_major > version._major)
	{
		return true;
	}
	else if (_major == version._major)
	{
		if (_minor > version._minor)
			return true;
		else if (_minor == version._minor)
			return _revision > version._revision;
	}
	return false;
}


bool Version::operator >= (const Version& version) const
{
	if (_major > version._major)
	{
		return true;
	}
	else if (_major == version._major)
	{
		if (_minor > version._minor)
			return true;
		else if (_minor == version._minor)
			return _revision >= version._revision;
	}
	return false;
}


} } // namespace Poco::OSP
