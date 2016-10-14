macchina.io
===========

*An open-source toolkit for building embedded IoT applications that connect sensors, devices and cloud services.*
						
macchina.io is a new open source software toolkit for quickly building
embedded applications for the Internet of Things that run on Linux-based
devices like the Raspberry Pi, Beaglebone or RED brick. macchina.io
implements a web-enabled, modular and extensible JavaScript and C++
runtime environment and provides readily available, easy to use building
blocks that allow your application to talk to various sensors and
devices, as well as cloud services.

macchina.io is based on the [POCO C++ Libraries](http://pocoproject.org) and
uses the [V8 JavaScript engine](https://code.google.com/p/v8/).

For more information, including documentation, please see the 
[macchina.io website](http://macchina.io).


Build Status
------------

- Travis: [![Travis Build Status](https://travis-ci.org/macchina-io/macchina.io.png?branch=develop)](https://travis-ci.org/macchina-io/macchina.io/)


Prerequisites
-------------

  - GNU Make
  - GNU C++ (g++) on Linux or Clang++ on OS X
  - OpenSSL headers and libraries 
  - Python (for building V8)


Getting Started
---------------

For the impatient, using a Linux or OS X machine:

    $ git clone https://github.com/macchina-io/macchina.io.git
    $ cd macchina.io
    $ git checkout master
    $ make -s -j8 DEFAULT_TARGET=shared_release

Then, on Linux:

    $ export LD_LIBRARY_PATH=`pwd`/platform/lib/Linux/x86_64
    $ cd server
    $ bin/Linux/x86_64/macchina
  
On OS X:

    $ export DYLD_LIBRARY_PATH=`pwd`/platform/lib/Darwin/x86_64
    $ cd server
    $ bin/Darwin/x86_64/macchina
  
Then direct your favorite web browser to <http://localhost:22080> and log in with username 'admin' and password 'admin'.

For more detailed instructions, including how to cross-compile for embedded Linux targets, 
as well as an introduction to writing JavaScript code for macchina.io, see
the [documentation](http://macchina.io/docs/index.html), specifically
[Introduction and Overview](http://macchina.io/docs/00100-MacchinaIntroduction.html) and 
[Getting Started with macchina.io](http://macchina.io/docs/00100-MacchinaIntroduction.html).


Project Status
--------------

macchina.io is still in development. The core platform code is done and considered stable
(it's based on code having seen heavy production use for a few years already). Current work
focuses on adding additional sensor, device and cloud service interfaces, as well as
refining the existing interfaces.


Contributions
-------------

We welcome contributions! Specifically we're looking for new sensor and device implementations, as well as additional protocols. Please see our [CONTRIBUTING](https://github.com/macchina-io/macchina.io/blob/develop/CONTRIBUTING.md) document to get started.
