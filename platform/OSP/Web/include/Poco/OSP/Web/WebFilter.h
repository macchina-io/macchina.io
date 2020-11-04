//
// WebFilter.h
//
// Library: OSP/Web
// Package: Web
// Module:  WebFilter
//
// Definition of the WebFilter class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Web_WebFilter_INCLUDED
#define OSP_Web_WebFilter_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <istream>
#include <map>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebFilter
	/// A WebFilter is used to process a bundle resource before it is
	/// sent to the client. This can be used, e.g., to implement web
	/// pages containing server-side scripts.
{
public:
	using Args = std::map<std::string, std::string>;
		/// Arguments for the WebFilter instance (from extension point).

	virtual ~WebFilter();
		/// Destroys the WebFilter.

	virtual void process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle) = 0;
		/// Processes the given resourceStream and sends it as HTTP response
		/// for the given request.
		///
		/// The content-type of the response will initially be set to the content-type
		/// of the resource, but can be changed by the method.
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebFilter_INCLUDED
