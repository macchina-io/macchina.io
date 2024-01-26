#
# Protocols
#
ifdef MACCHINA_ENABLE_PROTOCOLS
ifdef MACCHINA_ENABLE_MQTT
SDK_DIRS += protocols/MQTT protocols/MQTT/skel
endif
ifdef MACCHINA_ENABLE_XBEE
SDK_DIRS += protocols/XBee
endif
ifdef MACCHINA_ENABLE_BTLE
SDK_DIRS += protocols/BtLE
endif
ifdef MACCHINA_ENABLE_UDP
SDK_DIRS += protocols/UDP
endif
ifdef MACCHINA_ENABLE_MODBUS
SDK_DIRS += protocols/Modbus protocols/Modbus/skel
endif
ifdef MACCHINA_ENABLE_MODBUS_RTU
SDK_DIRS += protocols/Modbus/RTU
endif
ifdef MACCHINA_ENABLE_MODBUS_TCP
SDK_DIRS += protocols/Modbus/TCP
endif
ifdef MACCHINA_ENABLE_MODBUS_DEVICE
SDK_DIRS += protocols/Modbus/Device
endif
ifdef MACCHINA_ENABLE_CAN
SDK_DIRS += protocols/CAN
endif
ifdef MACCHINA_ENABLE_WEBTUNNEL
SDK_DIRS += protocols/WebTunnel
endif
endif # MACCHINA_ENABLE_PROTOCOLS


#
# Devices
#
ifdef MACCHINA_ENABLE_DEVICES
SDK_DIRS += devices/Devices devices/Devices/skel
ifdef MACCHINA_ENABLE_DATAPOINTS
SDK_DIRS += devices/Datapoints devices/Datapoints/skel
endif
ifdef MACCHINA_ENABLE_GNSS
SDK_DIRS += devices/GNSS/NMEA
endif
endif # MACCHINA_ENABLE_DEVICES


#
# Services
#
ifdef MACCHINA_ENABLE_SERVICES
ifdef MACCHINA_ENABLE_WEBEVENT
SDK_DIRS += services/WebEvent
endif
ifdef MACCHINA_ENABLE_SETTINGS
SDK_DIRS += services/Settings
endif
ifdef MACCHINA_ENABLE_DEVICESTATUS
SDK_DIRS += services/DeviceStatus
endif
ifdef MACCHINA_ENABLE_NETWORKENVIRONMENT
SDK_DIRS += services/NetworkEnvironment
endif
ifdef MACCHINA_ENABLE_UNITSOFMEASURE
SDK_DIRS += services/UnitsOfMeasure
endif
ifdef MACCHINA_ENABLE_MOBILECONNECTION
SDK_DIRS += services/MobileConnection
endif
endif # MACCHINA_ENABLE_SERVICES
