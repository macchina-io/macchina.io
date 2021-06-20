![macchina.io][logo]

*macchina.io Edge Device SDK is a powerful application software platform for IoT devices.*

With macchina.io you can rapidly build and deploy device applications that communicate with devices, sensors, actuators, cloud services, and humans.

macchina.io provides a web-enabled, secure, modular and extensible C++ and JavaScript IoT application environment on top of Linux, consisting of middleware, protocols and rich APIs.
macchina.io provides ready-to-use and industry proven software building blocks that enable applications to collect, process, filter, analyze and visualize sensor, machine and process data locally, directly where it originates, and where the action happens.
macchina.io enables IoT edge and fog computing.

macchina.io runs on Linux-based devices, including IoT gateways, industrial computing devices, and prototyping platforms like the Raspberry Pi, Beaglebone and MangOH.

macchina.io is based on the [POCO C++ Libraries](https://pocoproject.org) and
uses the [V8 JavaScript engine](https://developers.google.com/v8/).

For more information, including [documentation](https://macchina.io/docs), please see the
[macchina.io website](https://macchina.io). There are also a couple of useful articles and How-To's in the
[project wiki](https://github.com/macchina-io/macchina.io/wiki).


Build Status
------------

[![macchina.io-ci](https://github.com/macchina-io/macchina.io/actions/workflows/ci.yml/badge.svg?branch=develop)](https://github.com/macchina-io/macchina.io/actions/workflows/ci.yml)


Prerequisites
-------------

  - GNU Make 3.81 or newer
  - Linux: GNU C++ (g++) 5.0 or newer; alternatively Clang++ 3.4 or newer (C++14)
  - macOS: Clang++ (Apple LLVM) 10.0 or newer
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

    $ export LD_LIBRARY_PATH=`pwd`/platform/lib/Linux/x86_64:`pwd`/server/bin/Linux/x86_64/codeCache
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

License
-------

macchina.io IoT Edge Device SDK is dual-licensed under a [commercial license](https://macchina.io/sdk_licensing.html)
and the [GPLv3](LICENSE.html). The commercial license gives you the full rights to create and distribute software and devices on
your own terms without any GPL obligations. With the commercial license you also have access to professional support and maintenance,
as well as additional features.
See [this table](https://macchina.io/sdk_licensing.html#table) for a comparison between
GPLv3-licensed and commercial-licensed macchina.io IoT Edge Device SDK features.

Contributions
-------------

Please see our [CONTRIBUTING](https://github.com/macchina-io/macchina.io/blob/develop/CONTRIBUTING.md)
document to get started.

[logo]: doc/images/macchina_logo_320.png "macchina.io Logo"

