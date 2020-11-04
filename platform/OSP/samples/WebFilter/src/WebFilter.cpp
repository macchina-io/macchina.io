//
// WebFilter.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/WebFilter.h"
#include "Poco/OSP/Web/WebFilterFactory.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include "Poco/ClassLibrary.h"


class DateTimeFilter: public Poco::OSP::Web::WebFilter
{
public:
	void process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle)
	{
		std::string content;
		Poco::StreamCopier::copyToString(resourceStream, content);
		std::string dateTime = Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT);
		Poco::replaceInPlace(content, std::string("$$DATETIME$$"), dateTime);
		response.setContentType("text/html");
		response.send() << content;
	}
};


class DateTimeFilterFactory: public Poco::OSP::Web::WebFilterFactory
{
public:
	Poco::OSP::Web::WebFilter* createFilter(const Poco::OSP::Web::WebFilter::Args& args)
	{
		return new DateTimeFilter;
	}
};


POCO_BEGIN_NAMED_MANIFEST(WebFilter, Poco::OSP::Web::WebFilterFactory)
	POCO_EXPORT_CLASS(DateTimeFilterFactory)
POCO_END_MANIFEST
