# Release 2024.1 - 2024-03-XX

  - Upgraded JavaScript engine to a newer V8 version (v8.7)
  - Various improvements to the JavaScript engine, including new File and Crypto APIs
  - Improvements to JavaScript Server Page and Servlet system, including support
    for file uploads.
  - Added support for organizing devices and datapoints in a tree hierarchy
  - Added Datapoints library
  - BtLE/BlueZ now implements an improved PeripheralBrowser service.
  - BtLE now has a new PeripheralManager service for dynamically creating
    and managing generic GATTPeripheral services for specific peripheral devices.
  - Added support for implementing Modbus devices
  - Added Modbus DatapointsServer
  - Added REST APIs for user and permissions management, as well as
    bundle and systems management
  - New services: Mailer, SMS and Settings.
  - Support for enabling/disabling components when building.
  - Upgraded POCO to release 1.11.8
  - Upgraded Remoting and OSP frameworks
  - Upgraded Paho to 1.3.12
  - Countless minor improvements.


# Release 2022.1 - 2022-06-22

  - upgraded POCO to release 1.11.3
  - upgraded OSP and RemotingNG frameworks (see respective release notes)
  - add support for building without JavaScript engine


# Release 2021.1 - 2021-08-11

  - License change: changed license of open source version to GPLv3
  - upgraded POCO to release 1.11.0
  - upgraded OSP and RemotingNG frameworks (see respective release notes)
  - MQTT: support for MQTT version 5, upgrade bundled Paho library
  - JavaScript: new UUID object
  - JavaScript: fixed potential heap corruption with asynchronous HTTP requests
  - JavaScript: fixed potential double free in BridgeWrapper
  - JavaScript: HTTP request and response object have new headers property
  - JavaScript: fix a race condition when stopping a script
  - JavaScript: add toJSON() to Buffer, DateTime, LocalDateTime and UUID objects
  - Upgrade OpenLayers to newer version to fix Safari display issues


# Release 2020.1 - 2020-02-29

  - upgraded POCO to release 1.10.1
  - updated OSP and Remoting frameworks (see their respective release notes for details)
  - modernized codebase to use C++14
  - JavaScript: fixed an unhandled exception in RecordSet.toJSON() if record set is empty
  - JavaScript: fixed potential memory leaks due to wrong v8::Persistent use in
    some places
  - JavaScript: optimized handling of timer callbacks to avoid excessive delays when
    stopping a script with 10000s of timers
  - BtLE has been upgraded to work with current versions
    of bluepy-helper
  - BtLE: it's now possible create basic Peripheral devices and use them from JavaScript
  - Modbus: added ModbusMaster::reset() method
  - added device interface for cameras
  - various minor improvements and fixes


# Release 0.11.0 - 2019-09-18

  - upgraded POCO to release 1.9.4
  - updated OSP and Remoting frameworks
  - Various smaller fixes and improvements


# Release 0.10.0 - 2018-11-06

  - upgraded POCO to release 1.9.0
  - OSP: added ServiceListener class (including JS bindings)
  - OSP: added Bundle-PreventUninstall manifest property
  - Added various samples
  - Remoting: added support for std::array and Poco::array
  - Added support for CAN bus (via Linux SocketCAN)
  - JS Data binding: added executeNonQuery() method which does not create a RecordSet result
  - added UnitsOfMeasure service
  - OSP: added StripBundle utility
  - OSP Web: improved support for framework-level CSRF/XSRF protection
  - Web user interface: fix potential XSRF issues
  - Naming of device services: use port or device ID from config properties instead of index
  - Various smaller fixes and improvements


# Release 0.9.0 - 2018-01-12

  - upgraded POCO to final release 1.8.1
  - OSP: added support for modules


# Release 0.8.0 - 2017-12-18

  - upgraded POCO to pre-release 1.8.1
  - upgraded V8 to release 6.2
  - OSP: added CodeCacheUtility
  - Web user interface: high-dpi (retina) display support
  - Added SensorLog sample
  - Added MobileConnectionService
  - JavaScript: system.exec now returns a StringObject, with an exitStatus property
  - MQTT: upgrade bundled Paho library to release 1.3; support binary message payloads in JS
  - MQTT: Added support to specify/enforce TLS version for MQTT client
  - Support for Linux GPIO
  - RemoteGen: added support for @optional attribute (inverse of @mandatory)
  - Added Modbus/TCP support
  - Added support for Bosch CISS industrial multi-sensor device
  - Various smaller fixes and improvements


# Release 0.7.0 - 2017-04-17

  - upgraded POCO to release 1.7.8p2
  - Remoting: Added a new framework for authentication and authorization
  - RemoteGen bugfix: fix: don't generate () for empty default initialization in Skeleton code
  - RemoteGen bugfix: generate correct code for EventDispatcher and EventSubscriber for
    classes that inherit events from base classes
  - OSP: improved error message when starting a bundle fails because a dependency failed to start
  - JavaScript engine modularization: HTTP and Database classes are now in their own bundles/modules
  - MQTT/Paho: fix socket leak if connect fails
  - added UDP/6LoWPAN support
  - improved Modbus support
  - improved BtLE support
  - added support for Bosch XDK device


# Release 0.6.0 - 2016-10-11

  - upgraded POCO to release 1.7.6
  - make JS/Core, JS/Net, JS/Data and JS/Bridge build on Windows (including VS project files)
  - allow specifying a script memory limit through the osp.js.memoryLimit bundle property
    (also for JavaScript Servlets and Server Pages)
  - fixed memory usage issues in JavaScript
  - improved script stopping behavior (fix a race condition introduced in 0.5.0)
  - OSP: added BundleContext::listBundles() and BundleLoader::listBundles() overloads
    accepting a BundleFilter; BundleRepository: add installBundle() overloads that take a
    bundle repository path.
  - various minor fixes


# Release 0.5.0 - 2016-10-06

  - fixed a memory usage issue with Session wrapper in JavaScript servlet engine
  - handle potentially empty V8 handles returned by *::New()
  - upgrade bundled Paho to 1.1.0
  - fixed a bug in RemoteGen: generated serializers and deserializers for
    classes/structs using more than one level of inheritance would only serialize
    members of direct base class.
  - various minor fixes


# Release 0.4.0 - 2016-09-23

  - Script Scheduler improvements (@once) and documentation.
  - Added POCO Redis library to platform
  - Moved serial port library to platform


# Release 0.3.0 - 2016-08-29

Another developer preview release.

  - Updated bundled POCO libraries to 1.7.5
  - Added NetworkEnvironmentService
  - Remoting improvements


# Release 0.2.0 - 2016-08-08

Second developer preview release.


# Release 0.1.0 - 2015-03-10

This is the first release of macchina.io, released with the intent to get
early feedback from the IoT developer community.

macchina.io is still in development. The core platform code is done and
considered stable (it's based on code having seen heavy production use
for a few years already). Work leading to 1.0 release focuses on adding
additional sensor, device and cloud service interfaces, as well as improving
the existing interfaces.

