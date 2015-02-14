#
# Makefile
#
# $Id: //poco/1.6/OSP/Makefile#1 $
#
# Makefile for Poco OSP
#

include $(POCO_BASE)/build/rules/global

objects = Bundle BundleProperties BundleEvent BundleManifest OSPException \
	BundleActivator BundleEvents BundleStorage ServiceRegistry \
	BundleContext BundleFile CodeCache Version SystemEvents \
	BundleDirectory BundleLoader LanguageTag VersionRange \
	BundleRepository Service Properties QLExpr QLParser QLTokens \
	ServiceEvent ServiceFactory ServiceRef \
	ExtensionPoint ExtensionPointService \
	BundleFactory BundleContextFactory BundleStreamFactory \
	Configuration Preferences PreferencesEvent PreferencesService \
	BundleInstallerService OSPSubsystem AuthService

target         = PocoOSP
target_version = 2
target_libs    = PocoZip PocoUtil PocoXML PocoFoundation $(POCO_LICENSING)

include $(POCO_BASE)/build/rules/lib
