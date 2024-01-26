#! /bin/sh
if [ ! -f /opt/macchina/var/lib/macchina.auth.sqlite ] ; then
	cp /opt/macchina/etc/macchina.auth.sqlite.default /opt/macchina/var/lib/macchina.auth.sqlite
fi
mkdir -p /opt/macchina/var/lib/bundles
/opt/macchina/bin/macchina --config=/opt/macchina/etc/macchina.properties
