#
# Makefile
#
# Makefile for Poco WebTunnel Samples
#

.PHONY: projects
clean all: projects
projects:
	$(MAKE) -C WebTunnelClient $(MAKECMDGOALS)
	$(MAKE) -C WebTunnelSSH $(MAKECMDGOALS)
	$(MAKE) -C WebTunnelVNC $(MAKECMDGOALS)
	$(MAKE) -C WebTunnelAgent $(MAKECMDGOALS)
