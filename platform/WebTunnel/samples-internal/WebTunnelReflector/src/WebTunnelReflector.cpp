//
// WebTunnelReflector.cpp
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part, except
// with explicit permission.
//


#include "Poco/WebTunnel/PortReflector.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include "Poco/NumberParser.h"
#include <iostream>


using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;


class ReflectorRequestHandler: public HTTPRequestHandler
	/// Handle a WebSocket connection.
{
public:
	ReflectorRequestHandler(Poco::WebTunnel::PortReflector& portReflector):
		_portReflector(portReflector)
	{
	}
	
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		Application& app = Application::instance();
		try
		{			
			std::string proto = request.get("Sec-WebSocket-Protocol", "");
			Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket;
			if (proto == "com.appinf.webtunnel.server/1.0")
			{
				response.set("Sec-WebSocket-Protocol", proto);
				pWebSocket = new Poco::Net::WebSocket(request, response);
				_portReflector.addServerSocket(pWebSocket, "ac9667bb-6032-4267-af61-9a7aafd40479");
			}
			else if (proto == "com.appinf.webtunnel.client/1.0")
			{
				response.set("Sec-WebSocket-Protocol", proto);
				std::string portStr = request.get("X-WebTunnel-RemotePort", "");
				unsigned port;
				if (!portStr.empty() && Poco::NumberParser::tryParseUnsigned(portStr, port) && port > 0 && port < 65536)
				{
					pWebSocket = new Poco::Net::WebSocket(request, response);
					try
					{
						_portReflector.addClientSocket(pWebSocket, "ac9667bb-6032-4267-af61-9a7aafd40479", static_cast<Poco::UInt16>(port));
					}
					catch (Poco::NotFoundException&)
					{
						pWebSocket->shutdown(Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, "No connection to target available");
					}
				}
				else
				{
					pWebSocket = new Poco::Net::WebSocket(request, response);
					pWebSocket->shutdown(Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, "Missing or invalid X-WebTunnel-RemotePort header");
				}
			}
			else
			{
				pWebSocket = new Poco::Net::WebSocket(request, response);
				pWebSocket->shutdown(Poco::Net::WebSocket::WS_PROTOCOL_ERROR);
			}
		}
		catch (WebSocketException& exc)
		{
			app.logger().log(exc);
			switch (exc.code())
			{
			case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case Poco::Net::WebSocket::WS_ERR_NO_HANDSHAKE:
			case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}
	}
	
private:
	Poco::WebTunnel::PortReflector& _portReflector;
};


class RequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
	RequestHandlerFactory(Poco::WebTunnel::PortReflector& portReflector):
		_portReflector(portReflector)
	{
	}
	
	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		Application& app = Application::instance();
		app.logger().information("Request from " 
			+ request.clientAddress().toString()
			+ ": "
			+ request.getMethod()
			+ " "
			+ request.getURI()
			+ " "
			+ request.getVersion());
			
		for (HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it)
		{
			app.logger().debug(it->first + ": " + it->second);
		}
		
		return new ReflectorRequestHandler(_portReflector);
	}
	
private:
	Poco::WebTunnel::PortReflector& _portReflector;
};


class WebTunnelReflector: public Poco::Util::ServerApplication
{
public:
	WebTunnelReflector(): _helpRequested(false)
	{
	}
	
	~WebTunnelReflector()
	{
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}
		
	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("WebTunnel reflector server for testing purposes.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested)
		{
			displayHelp();
		}
		else
		{
			// get parameters from configuration file
			unsigned short port = static_cast<Poco::UInt16>(config().getInt("reflector.port", 9980));
			int threads = config().getInt("reflector.threads", 64);
			
			Poco::WebTunnel::PortReflector portReflector(threads);
			
			// set-up a server socket
			ServerSocket svs(port);
			// set-up a HTTPServer instance
			HTTPServer srv(new RequestHandlerFactory(portReflector), svs, new HTTPServerParams);
			// start the HTTPServer
			srv.start();
			// wait for CTRL-C or kill
			waitForTerminationRequest();
			// Stop the HTTPServer
			srv.stop();
		}
		return Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
};


POCO_SERVER_MAIN(WebTunnelReflector)
