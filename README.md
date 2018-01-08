macchina.io
===========

*A toolkit for embedded IoT Edge and Fog Computing applications that connect sensors, devices and cloud services.*

macchina.io is an open source software toolkit for quickly building device applications
for the Internet of Things running on Linux-based devices like the Raspberry Pi,
Beaglebone or MangOH. macchina.io implements a web-enabled, modular and extensible C++
and JavaScript runtime environment and provides easy to use building blocks.
These enable applications to talk to various sensors, devices and cloud services, and to
process, analyze and filter sensor data locally, at the edge device or within the local
network ("fog").

macchina.io is based on the [POCO C++ Libraries](http://pocoproject.org) and
uses the [V8 JavaScript engine](https://code.google.com/p/v8/).

For more information, including documentation, please see the
[macchina.io website](http://macchina.io).


Build Status
------------

- Travis: [![Travis Build Status](https://travis-ci.org/macchina-io/macchina.io.png?branch=develop)](https://travis-ci.org/macchina-io/macchina.io/)


Prerequisites
-------------

  - GNU Make 3.81 or newer
  - Linux: GNU C++ (g++) 4.9 or newer; alternatively Clang++ 3.4 or newer
  - macOS: Clang++ (Apple LLVM) 8.0 or newer
  - OpenSSL headers and libraries (on macOS, via [Homebrew](http://brew.sh): `brew install openssl`)
  - Python 2.7 (for building V8)


Getting Started
---------------

For the impatient, using a Linux or macOS machine:

    $ git clone https://github.com/macchina-io/macchina.io.git
    $ cd macchina.io
    $ git checkout master
    $ make -s -j8 DEFAULT_TARGET=shared_release

Then, on Linux:

    $ export LD_LIBRARY_PATH=`pwd`/platform/lib/Linux/x86_64
    $ cd server
    $ bin/Linux/x86_64/macchina

On macOS:

    $ export DYLD_LIBRARY_PATH=`pwd`/platform/lib/Darwin/x86_64
    $ cd server
    $ bin/Darwin/x86_64/macchina

Then direct your favorite web browser to <http://localhost:22080> and log in with username 'admin' and password 'admin'.

For more detailed instructions, including how to cross-compile for embedded Linux targets,
as well as an introduction to writing JavaScript code for macchina.io, see
the [documentation](http://macchina.io/docs/index.html), specifically
[Introduction and Overview](http://macchina.io/docs/00100-MacchinaIntroduction.html) and
[Getting Started with macchina.io](http://macchina.io/docs/00100-MacchinaIntroduction.html).


Contributions
-------------

We welcome contributions! Specifically we're looking for new sensor and device implementations,
as well as additional protocols.
Please see our [CONTRIBUTING](https://github.com/macchina-io/macchina.io/blob/develop/CONTRIBUTING.md)
document to get started.
