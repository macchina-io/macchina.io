#
# Makefile
#
# Makefile for macchina.io Services
#

.PHONY: clean all

ifndef MACCHINA_HAVE_COMPONENTS
sinclude ../components.make
endif

clean all:
ifdef MACCHINA_ENABLE_SERVICES
ifdef MACCHINA_ENABLE_WEBEVENT
ifdef MACCHINA_ENABLE_OSP_WEBEVENT
	$(MAKE) -C WebEvent $(MAKECMDGOALS)
endif
endif
ifdef MACCHINA_ENABLE_SETTINGS
	$(MAKE) -C Settings $(MAKECMDGOALS)
endif
ifdef MACCHINA_ENABLE_DEVICESTATUS
	$(MAKE) -C DeviceStatus $(MAKECMDGOALS)
endif
ifdef MACCHINA_ENABLE_NETWORKENVIRONMENT
	$(MAKE) -C NetworkEnvironment $(MAKECMDGOALS)
endif
ifdef MACCHINA_ENABLE_UNITSOFMEASURE
	$(MAKE) -C UnitsOfMeasure $(MAKECMDGOALS)
endif
ifdef MACCHINA_ENABLE_MOBILECONNECTION
	$(MAKE) -C MobileConnection $(MAKECMDGOALS)
ifdef MACCHINA_ENABLE_MOBILECONNECTION_LEGATO
	$(MAKE) -C MobileConnection/Legato $(MAKECMDGOALS)
endif
endif
endif
