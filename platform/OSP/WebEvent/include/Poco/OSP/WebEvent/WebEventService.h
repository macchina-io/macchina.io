//
// WebEventService.h
//
// Library: OSP/WebEvent
// Package: WebEvent
// Module:  WebEventService
//
// Definition of the WebEventService interface.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_WebEvent_WebEventService_INCLUDED
#define OSP_WebEvent_WebEventService_INCLUDED


#include "Poco/OSP/WebEvent/WebEvent.h"
#include "Poco/OSP/Service.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/BasicEvent.h"
#include "Poco/AutoPtr.h"
#include <utility>


namespace Poco {
namespace OSP {
namespace WebEvent {


class OSPWebEvent_API WebEventService: public Poco::OSP::Service
	/// The WebEventService is a service that allows a web application
	/// server to notify clients running in a browser, using a RFC 6455
	/// WebSocket.
	///
	/// The way this service works is as follows:
	///
	/// JavaScript code running in the browser will open a WebSocket connection
	/// to the OSP web server (using path "/webevent") and send a single-frame
	/// text subscription message specifying the subjects to subscribe to. The format
	/// of the subscription message is:
	///
	///     SUBSCRIBE <subjectList> WebEvent/1.0
	///
	/// where <subjectList> is a comma-separated list of subject names not
	/// containing white space characters.
	///
	/// Subject names use a hierarchical, reverse DNS-style syntax, with the
	/// parts of the subject delimited by periods. Subject names must not
	/// contain spaces and their parts should be valid C++ identifiers.
	/// However, the latter restriction is not enforced.
	/// Subject names are hierarchical. A subscriber to
	/// a "parent" subject (e.g., "com.appinf.events") will also receive
	/// all "child" subjects (e.g., "com.appinf.events.someEvent" and
	/// "com.appinf.events.someOtherEvent").
	///
	/// A client can unsubscribe from specific events by either sending an
	/// unsubscribe request or by simply closing the WebSocket. The
	/// format of the UNSUBSCRIBE message is similar to the SUBSCRIBE message:
	///
	///     UNSUBSCRIBE <subjectList>|* WebEvent/1.0
	///
	/// where <subjectList> is a comma-separated list of subject names, as
	/// with the SUBSCRIBE message. Instead of a subject list, a single
	/// asterisk can be specified, which means unsubscribe from all
	/// subjects.
	///
	/// After the initial SUBSCRIBE message the client can send additional
	/// SUBSCRIBE or UNSUBSCRIBE messages, and thus dynamically change its
	/// subscriptions without having to re-establish the WebSocket.
	///
	/// Once a client has opened a WebSocket and sent the SUBSCRIBE
	/// message, the WebSocket connection will be "parked" on the server
	/// and only used when an event message needs to be sent to the
	/// client. This allows a very high number of simultaneous subscribers,
	/// since a single subscriber does not consume much server resources,
	/// except for the socket and some data overhead.
	/// Specifically, a specific thread for the WebSocket connection will only be
	/// used during the initial connection setup.
	///
	/// Notification messages sent to clients are single-frame text
	/// messages with the following format:
	///
	///     NOTIFY <subjectName> WebEvent/1.0\r\n
	///     <data>
	///
	/// where <subjectName> is the subjectName specified in the
	/// call to notify(), and <data> is the given data string, which
	/// typically should be a valid serialized JSON or XML document in UTF-8
	/// encoding, although any valid UTF-8 string can be sent.
	///
	/// A client can also sent notifications to other clients by sending
	/// a NOTIFY message to the server.
	///
	/// A client can send a NOTIFY message using the special subject
	/// "system.ping" to the server, and the server will respond with a
	/// NOTIFY using the subject "system.pong". This can be used as a heartbeat
	/// mechanism to verify that the connection to the server is alive.
	/// Any data sent with the ping message will be sent back with the pong
	/// message.
{
public:
	using Ptr = Poco::AutoPtr<WebEventService>;
	using NotificationEvent = std::pair<std::string, std::string>;

	Poco::BasicEvent<const Poco::Net::HTTPServerRequest*> requestReceived;
		/// Fired when a HTTP WebSocket upgrade request has been received.
		/// This can be used for authentication and authorization, or to
		/// reject the client's web socket connection for other reasons.
		/// If the delegate function sets the status code of the HTTP response
		/// to anything other than 200 (OK), the WebSocket connection will not
		/// be established.

	Poco::BasicEvent<const std::string> subscriptionRequestReceived;
		/// Fired when a subscription request for a new subject arrives.
		/// This event is fired once per subject subscription on a
		/// socket. To find out the number of clients subscribed to a subject,
		/// use the subscriberCount() call.

	Poco::BasicEvent<const std::string> unsubscriptionRequestReceived;
		/// Fired when an unsubscription request for a subject arrives.
		/// This event is fired once per unsubscription on a socket.
		/// To find out the number of clients subscribed to a subject,
		/// use the subscriberCount() call.

	Poco::BasicEvent<const NotificationEvent> notificationSent;
		/// Fired when a notification has been sent, either by calling
		/// notify(), or by a client sending a NOTIFY message to
		/// the server.
		///
		/// This event is fired for all subjects. It's the
		/// responsibility of the delegate function to filter out
		/// ignore events not of interest.

	virtual Poco::BasicEvent<const NotificationEvent>& subjectNotified(const std::string& subject) = 0;
		/// Fired when a notification has been sent for the given
		/// subject, either by calling notify(), or by a client sending a
		/// NOTIFY message to the server.

	virtual void notify(const std::string& subjectName, const std::string& data) = 0;
		/// Notify all registered subscribers to the given subject, using
		/// the given data, which is typically a serialized JSON or
		/// XML document in UTF-8 encoding.
		///
		/// Sending the notification is done asynchronously. If a notification cannot be
		/// delivered to a subscriber due to a network issue, the subscriber will be removed
		/// and its WebSocket closed.

	virtual int subscriberCount(const std::string& subject) = 0;
		/// Returns the number of subscribers to the subject.

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;

	static const std::string SERVICE_NAME;

protected:
	WebEventService();
		/// Creates the WebEventService.

	~WebEventService();
		/// Destroys the WebEventService.
};


} } } // namespace Poco::OSP::WebEvent


#endif // OSP_WebEvent_WebEventService_INCLUDED
