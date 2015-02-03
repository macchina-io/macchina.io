//
// JSSPage.cpp
//
// $Id: //poco/1.4/OSP/JS/src/JSSPage.cpp#2 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "JSSPage.h"
#include "Poco/String.h"
#include "Poco/NumberParser.h"


namespace Poco {
namespace OSP {
namespace JS {


JSSPage::JSSPage()
{
}


JSSPage::~JSSPage()
{
}


bool JSSPage::getBool(const std::string& property, bool deflt) const
{
	if (has(property))
	{
		const std::string& value = get(property);
		return Poco::icompare(value, "true") == 0
		    || Poco::icompare(value, "yes") == 0 
		    || Poco::icompare(value, "on") == 0;
	}
	else return deflt;
}


int JSSPage::getInt(const std::string& property, int deflt) const
{
	if (has(property))
	{
		return Poco::NumberParser::parse(get(property));
	}
	else return deflt;
}


} } } // namespace Poco::OSP::JS
