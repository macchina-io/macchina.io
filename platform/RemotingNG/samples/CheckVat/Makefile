#
# Makefile
#
# Makefile for CheckVat sample
#

include $(POCO_BASE)/build/rules/global

objects = \
	CheckVat \
	CheckVatApprox \
	CheckVatApproxResponse \
	CheckVatResponse \
	CheckVatService \
	CheckVatServiceClientHelper \
	CheckVatServiceProxy \
	CheckVatServiceProxyFactory \
	ICheckVatService \
	CheckVatClient

target         = CheckVat
target_version = 1
target_libs    = PocoRemotingNGSOAP PocoRemotingNG PocoUtil PocoNet PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
