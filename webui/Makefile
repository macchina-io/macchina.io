#
# Makefile
#
# Makefile for macchina.io Web UI
#

.PHONY: clean all js

ifdef ENABLE_JS
js_deps = js
endif

clean all: base $(js_deps)

base:
	$(MAKE) -C Common $(MAKECMDGOALS)
	$(MAKE) -C jQuery $(MAKECMDGOALS)
	$(MAKE) -C AngularJS $(MAKECMDGOALS)
	$(MAKE) -C AngularFileUpload $(MAKECMDGOALS)
	$(MAKE) -C AngularUITree $(MAKECMDGOALS)
	$(MAKE) -C Launcher $(MAKECMDGOALS)
	$(MAKE) -C BundleAdmin $(MAKECMDGOALS)
	$(MAKE) -C Ace $(MAKECMDGOALS)
	$(MAKE) -C OpenLayers $(MAKECMDGOALS)
	$(MAKE) -C Console $(MAKECMDGOALS)
	$(MAKE) -C Settings $(MAKECMDGOALS)
	$(MAKE) -C ChartJS $(MAKECMDGOALS)
	$(MAKE) -C MomentJS $(MAKECMDGOALS)
	$(MAKE) -C TinyColor $(MAKECMDGOALS)

js:
	$(MAKE) -C SystemInformation $(MAKECMDGOALS)
	$(MAKE) -C Devices $(MAKECMDGOALS)
	$(MAKE) -C Playground $(MAKECMDGOALS)
	$(MAKE) -C MQTT $(MAKECMDGOALS)
	$(MAKE) -C GPIO $(MAKECMDGOALS)
	$(MAKE) -C GNSSTracking $(MAKECMDGOALS)
