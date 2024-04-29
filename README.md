![macchina.io][logo]

# macchina.io EDGE (GPL)

*macchina.io EDGE is a powerful application software platform for IoT devices.*

This is the GPL-licensed version of macchina.io EDGE.

A [commercially-licensed version](https://macchina.io/edge) with an extended feature
set, full source code and professional support is available.

Note that this GPL-licensed version:

  1. is only occasionally updated,
  2. does not contain all features from the commercial version,
  3. is provided as-is, without any support or warranty of any kind.

With macchina.io EDGE you can rapidly build and deploy device applications that communicate with devices, sensors, actuators, cloud services, and humans.

macchina.io EDGE provides a web-enabled, secure, modular and extensible C++ and JavaScript IoT application environment on top of Linux, consisting of middleware, protocols and rich APIs.
macchina.io EDGE provides ready-to-use and industry proven software building blocks that enable applications to collect, process, filter, analyze and visualize sensor, machine and process data locally, directly where it originates, and where the action happens.
macchina.io EDGE enables IoT edge computing.

macchina.io EDGE runs on Linux-based devices, including IoT gateways, industrial computing devices, and prototyping platforms like the Raspberry Pi and Beaglebone.

macchina.io EDGE is based on the [POCO C++ Libraries](https://pocoproject.org) and
uses the [V8 JavaScript engine](https://v8.dev).

For more information, including [documentation](https://docs.macchina.io/edge/), please see the
[macchina.io website](https://macchina.io). There are also a couple of useful articles and How-To's in the
[project wiki](https://github.com/macchina-io/macchina.io/wiki).


## Prerequisites

  - GNU Make 3.81 or newer
  - Linux: GNU C++ (g++) 5.0 or newer; alternatively Clang++ 3.4 or newer (C++14)
  - macOS: Clang++ (Apple LLVM) 10.0 or newer
  - OpenSSL headers and libraries (on macOS, via [Homebrew](http://brew.sh): `brew install openssl`)
  - Python 3.9 or newer (for building V8)
  - Avahi or Bonjour SDK for DNS-SD Support (optional)

### Ubuntu

```
$ sudo apt-get install -y make g++ libssl-dev python-is-python3
```

### Raspberry Pi (64-bit)

```
$ sudo apt-get install -y git make g++ libssl-dev
```

Note: We recommend using a 64-bit version of Raspberry Pi OS.
The combination of a 64-bit kernel (default for recent Raspberry Pi OS versions)
with a 32-bit userland causes the build to fail.

### macOS (with Homebrew)

```
$ brew install openssl python@3.9
```

NOTE: On macOS, the python command must run Python 3.9 or newer in order to build V8.
If installed via Homebrew, add the following directory to your `$PATH`:

Apple Silicon: `/opt/homebrew/opt/python@3.9/libexec/bin`

Intel: `/usr/local/opt/python@3.9/libexec/bin`

## Getting Started

For the impatient, using a Linux or macOS machine:

```
$ git clone https://github.com/macchina-io/macchina.io.git
$ cd macchina.io
$ make -s -j8 DEFAULT_TARGET=shared_release
```

Then, on Linux (x86_64):

```
$ . env.bash
$ cd server
$ bin/Linux/x86_64/macchina
```

On Raspberry Pi (aarch64)

```
$ . env.basah
$ cd server
$ bin/Linux/aarch64/macchina
```

On macOS (Apple Silicon):

```
$ . env.zsh
$ cd server
$ bin/Darwin/arm64/macchina
```

Then direct your favorite web browser to <http://localhost:22080> and log in with username `admin` and password `admin`.

To build macchina.io EDGE without JavaScript support, you can pass `WITHOUT_JS=1` to `make`:

```
$ make -s -j8 WITHOUT_JS=1 DEFAULT_TARGET=shared_release
```

For more detailed instructions, including how to cross-compile for embedded Linux targets,
as well as an introduction to writing JavaScript code for macchina.io, see
the [documentation](http://macchina.io/docs/index.html), specifically
[Introduction and Overview](http://macchina.io/docs/00100-MacchinaIntroduction.html) and
[Getting Started with macchina.io](http://macchina.io/docs/00100-MacchinaIntroduction.html).


## Enabling or Disabling macchina.io EDGE Components

To control which components are built, the [`components.make`](components.make)
file can be edited. Comment or uncomment specific lines to control which
components are built.


## Licensing

macchina.io EDGE is dual-licensed under a commercial license and the GPLv3.
The commercial license gives you the full rights to create and distribute software and
devices on your own terms without any GPL obligations. With the commercial license you
also have access to professional support and maintenance, as well as many additional features.
See [this table](https://macchina.io/edge_licensing.html#table) for a comparison between GPLv3-licensed and commercial-licensed macchina.io EDGE features.


[logo]: doc/images/macchina_logo_320.png "macchina.io Logo"
