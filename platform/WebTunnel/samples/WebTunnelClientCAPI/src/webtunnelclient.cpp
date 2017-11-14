//
// webtunnelclient.cpp
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "webtunnelclient.h"
#include "Poco/WebTunnel/LocalPortForwarder.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#if defined(WEBTUNNEL_ENABLE_TLS)
#include "Poco/Net/HTTPSSessionInstantiator.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/RejectCertificateHandler.h"
#include "Poco/Net/SSLManager.h"
#endif


namespace
{
	Poco::Timespan connectTimeout(30, 0);
	Poco::Timespan remoteTimeout(900, 0);
	Poco::Timespan localTimeout(0);
};


int webtunnel_init(void)
{
	try
	{
		Poco::Net::initializeNetwork();

#if defined(WEBTUNNEL_ENABLE_TLS)
		Poco::Net::initializeSSL();
		Poco::Net::HTTPSSessionInstantiator::registerInstantiator();
#endif

		return webtunnel_ok;
	}
	catch (...)
	{
		return webtunnel_error;
	}
}


void webtunnel_cleanup(void)
{
	try
	{
#if defined(WEBTUNNEL_ENABLE_TLS)
		Poco::Net::HTTPSSessionInstantiator::unregisterInstantiator();
		Poco::Net::uninitializeSSL();
#endif

		Poco::Net::uninitializeNetwork();
	}
	catch (...)
	{
	}
}


int webtunnel_configure_tls(bool accept_unknown_cert, bool extended_verification, const char* ciphers, const char* ca_location)
{
#if defined(WEBTUNNEL_ENABLE_TLS)
	try
	{
		std::string cipherList;
		if (ciphers) 
			cipherList = ciphers;
		else
			cipherList = "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH";
		std::string caLocation;
		if (ca_location) caLocation = caLocation;
			
		Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pCertificateHandler;
		if (accept_unknown_cert)
			pCertificateHandler = new Poco::Net::AcceptCertificateHandler(false);
		else
			pCertificateHandler = new Poco::Net::RejectCertificateHandler(false);
		Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::TLSV1_CLIENT_USE, "", "", caLocation, Poco::Net::Context::VERIFY_RELAXED, 5, true, cipherList);
		pContext->enableExtendedCertificateVerification(extended_verification);
		Poco::Net::SSLManager::instance().initializeClient(0, pCertificateHandler, pContext);

		return webtunnel_ok;
	}
	catch (Poco::Exception&)
	{
		return webtunnel_error;
	}
#else
	return webtunnel_not_supported;
#endif
}


int webtunnel_configure_timeouts(int connect_timeout, int remote_timeout, int local_timeout)
{
	if (connect_timeout >= 0 && remote_timeout >= 0 && local_timeout >= 0)
	{
		connectTimeout = Poco::Timespan(connect_timeout, 0);
		remoteTimeout  = Poco::Timespan(remote_timeout, 0);
		localTimeout   = Poco::Timespan(local_timeout, 0);
		return webtunnel_ok;
	}
	else return webtunnel_error;
}


webtunnel webtunnel_create(unsigned short local_port, unsigned short remote_port, const char* remote_uri, const char* username, const char* password)
{
	try
	{
		Poco::URI uri;
		if (remote_uri)
			uri = std::string(remote_uri);
		else
			return NULL;
		std::string user;
		if (username)
			user = username;
		std::string pass;
		if (password)
			pass = password;
		Poco::WebTunnel::LocalPortForwarder* pLPF = new Poco::WebTunnel::LocalPortForwarder(local_port, remote_port, uri, new Poco::WebTunnel::DefaultWebSocketFactory(user, pass, connectTimeout));
		if (remoteTimeout > 0)
			pLPF->setRemoteTimeout(remoteTimeout);
		if (localTimeout > 0)
			pLPF->setLocalTimeout(localTimeout);
		return pLPF;
	}
	catch (Poco::Exception&)
	{
		return NULL;
	}
}


void webtunnel_destroy(webtunnel wt)
{
	Poco::WebTunnel::LocalPortForwarder* pLPF = reinterpret_cast<Poco::WebTunnel::LocalPortForwarder*>(wt);
	try
	{
		delete pLPF;
	}
	catch (...)
	{
	}
}


unsigned short webtunnel_local_port(webtunnel wt)
{
	Poco::WebTunnel::LocalPortForwarder* pLPF = reinterpret_cast<Poco::WebTunnel::LocalPortForwarder*>(wt);
	if (pLPF)
		return pLPF->localPort();
	else
		return 0;
}
