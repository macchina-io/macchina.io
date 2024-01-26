#
# This is the Dockerfile for macchina.io EDGE
#

#
# Stage 1: Build
#
FROM alpine:3.18 AS buildstage

# Install required components for building
RUN apk update \
 && apk add \
 	git \
    g++ \
    linux-headers \
    make \
    openssl-dev \
    libpq-dev \
    python3

# python must be python3
RUN ln -sf python3 /usr/bin/python

# Create user
RUN addgroup -S build && adduser -S -G build build

# Setup Directories
RUN mkdir -p /home/build/source \
	&& mkdir -p /home/build/install \
	&& chown -R build:build /home/build

# Fetch macchina.io EDGE Sources
ADD . /home/build/source/macchina.io/
RUN chown -R build:build /home/build

USER build:build
WORKDIR /home/build

# Build macchina.io EDGE
RUN cd /home/build/source/macchina.io \
	&& make -s -j8 DEFAULT_TARGE=shared_release PRODUCT=runtime -j`nproc` MACCHINA_ENABLE_DATA_POSTGRESQL=1 \
	&& make PRODUCT=runtime INSTALLDIR=/home/build/install install

#
# Stage 2: Install
#
FROM alpine:3.18 AS runstage

RUN apk update \
 && apk add \
    libstdc++ \
    openssl \
    libpq \
    ca-certificates

# Copy macchina.io EDGE
RUN mkdir -p /opt/macchina \
 && mkdir -p /opt/macchina/var/lib \
 && mkdir -p /opt/macchina/var/log \
 && mkdir -p /opt/macchina/var/cache/bundles

COPY --from=buildstage /home/build/install /opt/macchina
ADD docker/macchina.properties /opt/macchina/etc/macchina.properties
ADD docker/macchina.auth.sqlite /opt/macchina/etc/macchina.auth.sqlite.default
ADD docker/macchina.sh /opt/macchina/bin/macchina.sh
ADD server/sample-track.gpx /opt/macchina/etc/sample-track.gpx

# Create user (note: membership in dialout group is required for access to serial ports,
# including certain USB devices). We also add the gpio group for access to GPIOs on
# a Raspberry Pi (NOTE: for access to GPIOs (/sys/class/gpio files), the container
# must be run in privileged mode).
RUN addgroup -S macchina \
 && addgroup -g 997 gpio \
 && adduser -S -G macchina macchina \
 && adduser macchina dialout \
 && adduser macchina gpio

RUN chown -R macchina:macchina /opt/macchina
USER macchina

ENV HTTP_PORT=22080
ENV HTTPS_PORT=0
ENV TLS_SERVER_CERT=/opt/macchina/etc/macchina.pem
ENV TLS_SERVER_KEY=/opt/macchina/etc/macchina.pem
ENV LOGPATH=/opt/macchina/var/log/macchina.log
ENV LOGLEVEL=information
ENV LOGCHANNEL=console

ENV LD_LIBRARY_PATH=/opt/macchina/lib:/opt/macchina/var/cache/bundles
ENV PATH=/opt/macchina/bin:${PATH}

VOLUME /opt/macchina/var/log
VOLUME /opt/macchina/var/lib

CMD ["/opt/macchina/bin/macchina.sh"]
