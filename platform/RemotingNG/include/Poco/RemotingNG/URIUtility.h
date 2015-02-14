//
// URIUtility.h
//
// $Id: //poco/1.6/RemotingNG/include/Poco/RemotingNG/URIUtility.h#1 $
//
// Library: RemotingNG
// Package: RemotingNG
// Module:  URIUtility
//
// Definition of the URIUtility class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_URIUtility_INCLUDED
#define RemotingNG_URIUtility_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"


namespace Poco {
namespace RemotingNG {


class RemotingNG_API URIUtility
	/// This class provides utility methods for parsing and creating RemotingNG URIs.
{
public:
	static std::string createURIPath(const Identifiable::ObjectId& oid, const Identifiable::TypeId& tid, const std::string& protocol);
		/// Creates an URI path from the given input parameters.
		
	static std::string createURIAuthority(const std::string& host, Poco::UInt16 port);
		/// Creates an URI authority (e.g. host:port) from the given parameters.

	static void parseURIPath(const std::string& uri, Identifiable::ObjectId& oid, Identifiable::TypeId& tid, std::string& protocol);
		/// Parses an URI containing a path created by createURIPath().
		///
		/// Throws an exception if the URI format is not recognized.
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_URIUtility_INCLUDED
