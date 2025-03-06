//
// WebSession.h
//
// Library: OSP/Web
// Package: Web
// Module:  WebSession
//
// Definition of the WebSession class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Web_WebSession_INCLUDED
#define OSP_Web_WebSession_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Any.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace OSP {
namespace Web {


class WebSessionStore;


class OSPWeb_API WebSession
	/// A WebSession is used for tracking users between different
	/// HTTP(S) requests. WebSession objects are managed by
	/// a session manager (usually, an implementation of the WebSessionService).
	///
	/// The WebSession can also be used to store arbitrary data
	/// (attributes) in the form of key-value pairs between different
	/// requests. Poco::Any is used for storing values, so practically
	/// any object can be attached to a session.
	///
	/// A WebSession has a time out. If a WebSession instance is not
	/// accessed for a given time, it will be destroyed by the
	/// session manager.
	///
	/// Note that the iterator-based access methods (find(), begin(),
	/// end()) are not thread-safe.
	///
	/// When a new session is created, the session manager will generate a
	/// CSRF synchronizer token, which can be used in forms to prevent
	/// Cross-Site Request Forgery (CSRF) attacks. The name of the property
	/// is "#csrfToken". It can also be obtained by calling the csrfToken()
	/// member function.
{
public:
	Poco::BasicEvent<const WebSession*> sessionEnds;
		/// Fired before the session object is destroyed.

	using Attributes = std::map<std::string, Poco::Any>;
	using Ptr = Poco::SharedPtr<WebSession>;

	WebSession(const std::string& id, const std::string& csrfToken, Poco::Int64 version, int timeoutSeconds, const Poco::Net::IPAddress& clientAddress, Poco::AutoPtr<WebSessionStore> pStore, BundleContext::Ptr pContext);
		/// Creates a new WebSession with the given ID and time out.

	WebSession(const std::string& id, Poco::Int64 version, int timeoutSeconds, const Poco::Net::IPAddress& clientAddress, Poco::AutoPtr<WebSessionStore> pStore, BundleContext::Ptr pContext, Poco::Timestamp created, const Attributes& attrs);
		/// Creates a new WebSession with the given ID and time out.

	virtual ~WebSession();
		/// Fires a sessionEnds event and destroys the WebSession.

	const std::string& id() const;
		/// The unique identifier of the session.

	Poco::Int64 version() const;
		/// Returns the version number of the session.

	const Poco::Timestamp& created() const;
		/// Returns the creation time of the session, i.e. the time the user sent the first request.

	bool has(const std::string& key) const;
		/// Returns true iff the session has an attribute with the given value.

	const Poco::Any& get(const std::string& key) const;
		/// Returns the attribute with the given key.
		///
		/// Throws a Poco::NotFoundException
		/// if the attribute does not exist.

	template <typename T>
	T getValue(const std::string& key) const
		/// Convenience function that returns the attribute with the given key,
		/// casted to the desired type.
		///
		/// Throws a Poco::NotFoundException if the attribute does not exist.
		/// Throws a Poco::BadCastException if the cast is invalid.
	{
		const Poco::Any& any = get(key);
		return Poco::AnyCast<T>(any);
	}

	template <typename T>
	T getValue(const std::string& key, T deflt) const
		/// Convenience function that returns the attribute with the given key,
		/// casted to the desired type. If the attribute does not exist,
		/// the given default value is returned.
		///
		/// Throws a Poco::BadCastException if the cast is invalid.
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		Attributes::const_iterator it = _attrs.find(key);
		if (it != _attrs.end())
			return Poco::AnyCast<T>(it->second);
		else
			return deflt;
	}

	void set(const std::string& key, const Poco::Any& value);
		/// Sets/Overwrites an attribute value.

	template <typename T>
	void setValue(const std::string& key, T value)
		/// Sets/Overwrites an attribute value.
	{
		set(key, Poco::Any(value));
	}

	void erase(const std::string& key);
		/// Erases an attribute value from the session.

	Attributes::const_iterator find(const std::string& key) const;
		/// Searches for an attribute. Returns end() if not found.

	Attributes::const_iterator begin() const;
		/// Returns the begin iterator for attributes.

	Attributes::const_iterator end() const;
		/// Returns the end iterator for attributes.

	void clear();
		/// Erases all attributes.

	int timeout() const;
		/// Returns the timeout of the session in seconds.

	void timeout(int seconds);
		/// Sets a new timeout in seconds for the session. 

	const Poco::Net::IPAddress& clientAddress() const;
		/// Returns the IP address of the client holding the session.

	void access();
		/// Updates the expiration time.

	std::string csrfToken() const;
		/// Returns the CSRF synchronizer token for this session.

	// UniqueExpireCache support
	const Poco::Timestamp& getExpiration() const;
		/// Return the time when the session will expire.

	static const std::string CSRF_TOKEN;
		/// The name of the attribute storing the CSRF synchronizer token.

protected:
	void onBundleStopping(const void* pSender, BundleEvent& ev);
		/// When the bundle owning the session is stopped, all attributes are cleared.
		///
		/// After the bundle owning the session has been stopped and its libraries have
		/// been unloaded, virtual destructors of objects stored in the session
		/// might no longer be available. Therefore all attributes must be removed
		/// while their object's destructors are still available.

	void updateVersion(Poco::Int64 version);
		/// Updates the version if the new version is one higher than the current version.

	void accessImpl();
		/// Updates the expiration time.

	void clearImpl();
		/// Erases all attributes.

private:
	std::string          _id;
	Poco::Int64          _version;
	Poco::Timespan       _timeout;
	BundleContext::Ptr   _pContext;
	Poco::Timestamp      _created;
	Poco::Timestamp      _expiration;
	Poco::Net::IPAddress _clientAddress;
	Attributes           _attrs;
	Poco::AutoPtr<WebSessionStore> _pStore;

	mutable Poco::FastMutex _mutex;
	mutable Poco::FastMutex _timeoutMutex;
};


//
// inlines
//
inline const std::string& WebSession::id() const
{
	return _id;
}


inline Poco::Int64 WebSession::version() const
{
	return _version;
}


inline int WebSession::timeout() const
{
	Poco::FastMutex::ScopedLock lock(_timeoutMutex);

	return _timeout.totalSeconds();
}


inline const Poco::Timestamp& WebSession::created() const
{
	return _created;
}


inline const Poco::Net::IPAddress& WebSession::clientAddress() const
{
	return _clientAddress;
}


inline const Poco::Timestamp& WebSession::getExpiration() const
{
	Poco::FastMutex::ScopedLock lock(_timeoutMutex);

	return _expiration;
}


inline WebSession::Attributes::const_iterator WebSession::find(const std::string& key) const
{
	return _attrs.find(key);
}


inline WebSession::Attributes::const_iterator WebSession::begin() const
{
	return _attrs.begin();
}


inline WebSession::Attributes::const_iterator WebSession::end() const
{
	return _attrs.end();
}


inline std::string WebSession::csrfToken() const
{
	return getValue<std::string>(CSRF_TOKEN);
}


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebSession_INCLUDED
