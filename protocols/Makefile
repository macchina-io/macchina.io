#
# Makefile
#
# Makefile for macchina.io Protocols
#

.PHONY: clean all

clean all:
	$(MAKE) -C MQTT $(MAKECMDGOALS)
	$(MAKE) -C XBee $(MAKECMDGOALS)
	$(MAKE) -C BtLE $(MAKECMDGOALS)
	$(MAKE) -C BtLE/BlueZ $(MAKECMDGOALS)
	$(MAKE) -C UDP $(MAKECMDGOALS)
	$(MAKE) -C Modbus $(MAKECMDGOALS)
	$(MAKE) -C Modbus/RTU $(MAKECMDGOALS)
	$(MAKE) -C Modbus/TCP $(MAKECMDGOALS)
	$(MAKE) -C CAN $(MAKECMDGOALS)
	$(MAKE) -C CAN/SocketCAN $(MAKECMDGOALS)
	$(MAKE) -C WebTunnel $(MAKECMDGOALS)
