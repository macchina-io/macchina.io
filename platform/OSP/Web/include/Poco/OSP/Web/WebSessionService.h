//
// WebSessionService.h
//
// Library: OSP/Web
// Package: Web
// Module:  WebSessionService
//
// Definition of the WebSessionService interface.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Web_WebSessionService_INCLUDED
#define OSP_Web_WebSessionService_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Web/WebSession.h"


namespace Poco {
namespace OSP {
namespace Web {


template <class Request>
class WebSessionService: public Service
	/// A WebSessionService manages WebSession objects.
	///
	/// How an implementation of the WebSessionService actually
	/// associates WebSession objects with user sessions in a
	/// web browser is up to the implementation. A typical way
	/// to do this would be to set a cookie referencing the
	/// WebSession in the user's web browser.
	///
	/// Sessions are always associated with a certain application.
	/// This allows for different applications running in one OSP
	/// container to each have their own session object.
	///
	/// Application names should follow the usual OSP reverse-DNS
	/// naming schema. Specifying an empty application name is valid.
{
public:
	virtual WebSession::Ptr find(const std::string& appName, const Request& request) = 0;
		/// Return a WebSession object for the application specified by appName and
		/// the given HTTP request if one exists, or a null pointer otherwise.

	virtual WebSession::Ptr get(const std::string& appName, const Request& request, int expireSeconds, BundleContext::Ptr pContext) = 0;
		/// Return a WebSession object for the application specified by appName and
		/// the given HTTP request. If no session is associated with the given request,
		/// a new session is created with the given expiration time.

	virtual WebSession::Ptr create(const std::string& appName, const Request& request, int expireSeconds, BundleContext::Ptr pContext) = 0;
		/// Creates a new WebSession object with the given expiration time for the application
		/// given by appName and the given HTTP request, and associates the WebSession with
		/// the browser's user session.

	virtual void remove(WebSession::Ptr ptr) = 0;
		/// Removes a session from the manager, if it exists. Does nothing if the
		/// session is not known to the session manager.

	virtual void removeForUser(const std::string& username) = 0;
		/// Removes all sessions for the given username.

	// Service
	const std::type_info& type() const
	{
		return typeid(WebSessionService);
	}

	bool isA(const std::type_info& otherType) const
	{
		std::string name(typeid(WebSessionService).name());
		return name == otherType.name() || Service::isA(otherType);
	}

protected:
	WebSessionService()
	{
	}

	~WebSessionService()
	{
	}
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebSessionService_INCLUDED
