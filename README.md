macchina.io
===========

macchina.io is a new open source software toolkit for quickly building
embedded applications for the Internet of Things that run on Linux-based
devices like the Raspberry Pi, Beaglebone or RED brick. macchina.io
implements a web-enabled, modular and extensible JavaScript and C++
runtime environment and provides readily available, easy to use building
blocks that allow your application to talk to various sensors and
devices, as well as cloud services.

macchina.io is based on the [POCO C++ Libraries](http://pocoproject.org) and
integrates it with the [V8 JavaScript engine](https://code.google.com/p/v8/).

For more information, including documentation, please see the 
[macchina.io website](http://macchina.io).


Build Status
------------

- Travis: [![Travis Build Status](https://travis-ci.org/macchina-io/macchina.io.png?branch=develop)](https://travis-ci.org/macchina-io/macchina.io/)


Project Status
--------------

macchina.io is still in development. The core framework code is done and considered stable
(it's based on code having seen heavy production use for a few years already). Current work
focuses on adding additional sensor and device interfaces, as well as a MQTT client.
Also, the web user interface still needs to be done.


Contributions
-------------

We welcome contributions! Specifically we're looking for new sensor and device implementations, as well as additional protocols. Please see our [CONTRIBUTING](https://github.com/macchina-io/macchina.io/blob/develop/CONTRIBUTING.md) document to get started.
