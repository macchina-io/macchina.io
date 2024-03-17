//
// WebSessionStore.h
//
// Library: OSP/Web
// Package: Web
// Module:  WebSession
//
// Definition of the WebSessionStore class.
//
// Copyright (c) 2007-2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Web_WebSessionStore_INCLUDED
#define OSP_Web_WebSessionStore_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Service.h"
#include <utility>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebSessionStore: public Poco::OSP::Service
	/// WebSessionStore is an optional service that is used to persistently
	/// store WebSession objects.
{
public:
	using Ptr = Poco::AutoPtr<WebSessionStore>;

	virtual void saveSession(WebSession::Ptr pSession) = 0;
		/// Saves the given session.

	virtual std::pair<WebSession::Ptr, bool> loadSession(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, Poco::Int64 version = 0) = 0;
		/// Loads the persisted session with the given ID, but
		/// only if the stored version is greater than the given version.
		///
		/// The minimum stored version number is 1, so if version 0 is specified
		/// the session will always be loaded if it exists.
		///
		/// Returns {pSession, true} if a stored session with a higher version number exists.
		/// Returns {null, true} if a stored session exists with the same or lower version number.
		/// Returns {null, false} if no stored session with the given ID exists.

	virtual void expireSession(const std::string& sessionId, Poco::Timespan timeout) = 0;
		/// Resets the session expiration time.
		///
		/// A zero timeout immediately removes the session.

	virtual Poco::Int64 saveValue(const std::string& sessionId, const std::string& key, const Poco::Any& value) = 0;
		/// Saves the value of the given key for the given session.
		///
		/// Returns the new version number of the session.
		/// If the returned version number is one higher than
		/// the session's version number, the new version number
		/// can be stored.

	virtual Poco::Int64 removeValue(const std::string& sessionId, const std::string& key) = 0;
		/// Removes the given key from the given session.
		///
		/// Returns the new version number of the session.
		/// If the returned version number is one higher than
		/// the session's version number, the new version number
		/// can be stored.

	virtual Poco::Int64 clearValues(const std::string& sessionId) = 0;
		/// Removes all values from the session.

	virtual std::vector<std::string> sessionsByValue(const std::string& key, const Poco::Any& value) = 0;
		/// Returns a vector containing the session IDs of all sessions
		/// having a value with the given key and value. Typically, this
		/// is used to obtain all sessions for a given username.

	virtual std::size_t countSessions() = 0;
		/// Returns the total number of sessions in the store.

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebSessionStore_INCLUDED
