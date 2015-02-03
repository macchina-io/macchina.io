my-devices.net - WebTunnelServer Setup Instructions
===================================================

In order to set-up my-devices.net remote access to a device, 
the following steps must be performed.

1. Install the WebTunnelServer application on a system
2. Configure the WebTunnelServer server
3. Run the WebTunnelServer server
4. Log-in to my-devices.net

These steps are described in the following.


1. Installing the WebTunnelServer application on the system
-----------------------------------------------------------

To install the WebTunnelServer application on the system, copy the executable 
(WebTunnelServer.exe) and the configuration file (WebTunnelServer.properties) to a 
directory of your choice.

WebTunnelServer can optionally be run as a Windows service. This is done by invoking
WebTunnelServer with the /registerService command-line option. 
Note that the script must be started from a command shell with Administrator privileges. 
After installing the service, it must be started. This can be done with the Services 
MMC applet (Start > Control Panel > Administrative Tools > Services;
look for the service named "WebTunnelServer") or from the command shell:

> net start "WebTunnelServer"

To unregister the service, invoke WebTunnelServer with the /unregisterService option. 
The service must be stopped
before it can be uninstalled.


2. Configuring the WebTunnelServer application
----------------------------------------------

Configuring the WebTunnelServer application is done by editing the configuration file
WebTunnelServer.properties. IMPORTANT: You must change the "webtunnel.domain"
setting to the UUID assigned to your account on the reflector server.
You can find out your domain UUID by logging in to the reflector server and
going to the Account page by clicking the user icon in the upper right of the
browser window.
If you do not change this setting, your device will not be visible to you
when you log-in to my-devices.net. You must also change the "webtunnel.host"
setting to match the IP address of your target device. If your device's web
server is running on a port other than 80, you must also change "webtunnel.ports"
and "webtunnel.httpPort" accordingly.
For the first tests, it should not be necessary to modify anything else -- 
the defaults should work fine.

Following is a description of the settings in the configuration file:

  - webtunnel.host: The IP address of the target device where TCP connections will
    be forwarded to.
  - webtunnel.ports: A comma-separated list of ports that will be forwarded. This should 
    include the web server port (typically 80) and any other port that should be
    available remotely (e.g., SSH port 22).
  - webtunnel.httpPort: The port the local (forwarded) web server is listening on. Must
    only be specified if a port other than 80 is used.
  - webtunnel.connectTimeout: The timout (in seconds) for connecting to the local 
    (forwarded) port.
  - webtunnel.localTimeout: The timeout (in seconds) for receiving data
    from the local port. Default is 30 seconds.
  - webtunnel.remoteTimeout: The timeout (in seconds) for the tunnel connection to
    the reflector server. If no data is received during that timespan, the 
    WebTunnelServer will send a special PING request to the server. If this is
    unanswered, the connection will be closed.
  - webtunnel.reflectorURI: The address (URI) of the reflector server. Must be a
    http or https URI, e.g.: http://reflector.my-devices.net.
  - webtunnel.username: The username the WebTunnelServer uses to authenticate itself 
    against the reflector. Format is <deviceId>@<domain>, where <deviceId> is a UUID that
    identifies the device and <domain> is another UUID that defines the "domain"
    the device belongs to. The domain is used to associate devices with user
    accounts on the reflector server.
  - webtunnel.deviceId: The UUID of the device, used to form the device's username.
    In the sample configuration file, the UUID is built from a prefix 
    (c9eebed5-8705-4763-8822-) and the device's Ethernet MAC address. This allows
    the same configuration file to be reused among different devices so that
    every device gets its unique UUID.
  - webtunnel.domain: The UUID of the domain the device belongs to. This must match the
    domain UUID assigned to your reflector server account, otherwise you 
    won't be able to see and access the device on the reflector server.
  - webtunnel.password: The password used to authenticate the device against the reflector 
    server. Currently device password verification on the reflector server is disabled, so 
    this can be left as-is.
  - tls.ciphers: A list of cipher suites to use for encryption. This should be balanced
    with the system's capabilities. For example, using AES256-SHA is quite secure,
    but on slower embedded devices the SSL/TLS handshake may take a very long time.
    DES-CBC3-SHA is not very secure, but fast also on less capable devices.
    The default (ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH) may not work well on smaller
    devices as a very slow cipher suite may be chosen.
  - http.timeout: The timeout (in seconds) for connecting to the reflector server.
  - http.proxy.enable: If set to true, a HTTP proxy server is used for connecting to the 
    reflector server.
  - http.proxy.host: The IP address or host name of the HTTP proxy server.
  - http.proxy.port: The port number of the HTTP proxy server.
  - http.proxy.username: The username for HTTP proxy authentication. Can be left empty
    if not required.
  - http.proxy.password: The password for HTTP proxy authentication. Can be left empty
    if not required.
  - logging.loggers.root.level: The default log level (or verbosity). Set to 
    "information" or "debug" for more log output, or set to "notice", "warning"
    or "error" for less.
  - logging.loggers.root.channel: The log channel for log output. Set to
    "file" if the WebTunnelServer is run as a Windows service. 
    
The rest of the setting sets up various logging channels. Please refer to
<http://pocoproject.org/slides/185-LoggingConfiguration.pdf> for more
information.


3. Running the WebTunnelServer application
------------------------------------------

Before you run the WebTunnelServer application make sure that your system can access
the internet. 

You can test connectivity with ping:

> ping reflector.my-devices.net

or

> ping 50.57.191.182
  
If this works, changes are good that WebTunnelServer will be able to connect
to the reflector service.

You can run WebTunnelServer interactively, by double-clicking the
WebTunnelServer.exe executable. Just make sure that the configuration
file WebTunnelServer.properties is in the same directory as the 
executable.

Alternatively, you can also start it from a Command Prompt.
The path to the configuration file can be given as argument:

> WebTunnelServer /config=WebTunnelServer.properties
  
After a few seconds, you should see the line:

  I Application: WebTunnel connection established.
  
(or something similar) if everything goes well and the
log level is set accordingly.

You can also ask for help:

> WebTunnelServer /help
  
This will show all available command line options.

As described above, WebTunnelServer can also run as a Windows service.


4. Log-in to my-devices.net
---------------------------

Direct your web browser of choice to my-devices.net reflector server at
<https://reflector.my-devices.net>. 
You will see the log-in screen. Enter your username and password and
click the Sign in button (or simply press RETURN) to sign in.

After signing in you will see a list of all your devices connected to the
reflector server. At first, your devices won't have names assigned, so
you'll see devices named "Unnamed Device". Click on the
name to go directly 
to the device's web server via the reflector server.
You can also click the 
[>] button to see and edit the device properties.

On the Device Properties screen you can click the "pencil" [/] button right
to a property value to edit the value. 
New properties can be added by clicking the [+] button at the bottom
of the table. 

Clicking the Home icon in the page header brings you back to
the Dashboard page.

