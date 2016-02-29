#
# Makefile
#
# $Id: //poco/1.7/OSP/testsuite/Makefile#1 $
#
# Makefile for Poco OSPCore testsuite
#

.PHONY: projects
all: projects

clean:
	$(MAKE) -f Makefile-Driver clean
	$(MAKE) -f Makefile-TestBundle clean

projects:
	$(MAKE) -f Makefile-Driver $(MAKECMDGOALS)
	$(MAKE) -f Makefile-TestBundle $(MAKECMDGOALS)
	$(MAKE) -f Makefile-TestBundle bundle
