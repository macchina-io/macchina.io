/*
// webtunnelclient.h
//
// The WebTunnel Client C API
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
*/


#ifndef WebTunnelClient_INCLUDED
#define WebTunnelClient_INCLUDED


/*
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WebTunnelClient_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WebTunnel_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
*/
#if defined(_WIN32) 
	#if defined(WebTunnelClient_EXPORTS)
		#define WebTunnelClient_API __declspec(dllexport)
	#else
		#define WebTunnelClient_API __declspec(dllimport)
	#endif
#endif


#if !defined(WebTunnelClient_API)
	#define WebTunnelClient_API
#endif


/*
// Automatically link WebTunnelClientCAPI library.
*/
#if defined(_MSC_VER)
	#if !defined(WebTunnelClient_EXPORTS)
		#if defined(_DEBUG)
			#pragma comment(lib, "WebTunnelClientd.lib")
		#else
			#pragma comment(lib, "WebTunnelClient.lib")
		#endif
	#endif
#endif


/*
// Client API
*/
enum WebTunnelResult
{
	webtunnel_ok = 0,
	webtunnel_error = 1,
	webtunnel_not_supported = 2
};


typedef void* webtunnel;


#ifdef __cplusplus
extern "C" {
#endif


/*
// webtunnel_init
//
// Initialize webtunnel client library. 
// Must be called before any other functions.
// Returns webunnel_ok if successful, or
// webtunnel_error otherwise.
*/
int WebTunnelClient_API webtunnel_init(void);


/*
// webtunnel_cleanup
//
// Cleanup webtunnel client library.
// Should be called when the library is no longer being used
// to cleanup internal state.
*/
void WebTunnelClient_API webtunnel_cleanup(void);


/*
// webtunnel_configure_timeouts
//
// Configure timeouts for WebTunnel connections.
//
// All timeouts are in seconds.
//
// connect_timeout is the timeout for setting up the initial HTTP connection
// to the reflector server.
//
// remote_timeout specifies the timeout of the tunnel connection to the reflector service.
// If no data has been received for this period, the client will send a PING
// message to the server. If the server does not reply to the PING, the connection
// will be closed.
//
// local_timeout specifies the timeout of the local socket connection.
// If no data has been received for this period, the connection will be closed.
*/
int webtunnel_configure_timeouts(int connect_timeout, int remote_timeout, int local_timeout);


/*
// webtunnel_configure_tls
//
// Sets up SSL/TLS parameters for the connection to the
// reflector server.
//
// If accept_unknown_cert is true, any server certificate, even without
// a valid chain, will be accepted.
//
// If extended_verification is true, extended certificate verification
// will be performed, which means that the certificate must contain the
// fully qualified domain name of the reflector server.
//
// A list of ciphers can be given in ciphers, using OpenSSL syntax
// (e.g., "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"). Can be NULL to use
// the default.
//
// ca_location contains the path to the file or directory containing 
// the CA/root certificates. Can be NULL to use the built-in root
// certificates.
//
// Returns webtunnel_ok if successful, or webtunnel_error if an error
// occured, or webtunnel_not_supported if no SSL/TLS support is available.
*/
int WebTunnelClient_API webtunnel_configure_tls(bool accept_unknown_cert, bool extended_verification, const char* ciphers, const char* ca_location);


/*
// webtunnel_create
//
// Creates a tunnel connection from the given local_port to remote_port on
// the remote machine, using the reflector server as intermediary.
// If local_port is 0, a suitable port number will be chosen automatically.
// The port number can be obtained by calling webtunnel_local_port().
//
// remote_uri contains the URI of the remote machine, using the http
// or https URI scheme. 
// Example: " https://0a72da53-9de5-44c8-9adf-f3d916304be6.my-devices.net"
//
// username and password are used for authentication against the reflector
// server.
//
// Returns NULL in case of an error.
*/
webtunnel WebTunnelClient_API webtunnel_create(unsigned short local_port, unsigned short remote_port, const char* remote_uri, const char* username, const char* password);


/*
// webtunnel_destroy
//
// Closes the given web tunnel connection.
*/
void WebTunnelClient_API webtunnel_destroy(webtunnel wt);


/*
// webtunnel_local_port
//
// Returns the local port number for forwarding
// connections.
*/
unsigned short WebTunnelClient_API webtunnel_local_port(webtunnel wt);


#ifdef __cplusplus
}
#endif


#endif /* WebTunnelClient_INCLUDED */
