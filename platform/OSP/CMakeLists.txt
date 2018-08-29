
add_library(PocoOSP SHARED
    src/BundleLoader.cpp
    src/Preferences.cpp
    src/BundleFactory.cpp
    src/BundleEvents.cpp
    src/BundleProperties.cpp
    src/BundleFile.cpp
    src/Properties.cpp
    src/PreferencesEvent.cpp
    src/CodeCache.cpp
    src/BundleInstallerService.cpp
    src/BundleStreamFactory.cpp
    src/BundleDirectory.cpp
    src/OSPSubsystem.cpp
    src/BundleManifest.cpp
    src/ServiceRef.cpp
    src/SystemEvents.cpp
    src/PreferencesService.cpp
    src/BundleStorage.cpp
    src/Bundle.cpp
    src/BundleEvent.cpp
    src/VersionRange.cpp
    src/LanguageTag.cpp
    src/BundleRepository.cpp
    src/ServiceRegistry.cpp
    src/ServiceFactory.cpp
    src/QLExpr.cpp
    src/OSPException.cpp
    src/BundleContextFactory.cpp
    src/ServiceEvent.cpp
    src/Configuration.cpp
    src/Version.cpp
    src/BundleContext.cpp
    src/QLParser.cpp
    src/ExtensionPoint.cpp
    src/ExtensionPointService.cpp
    src/BundleFilter.cpp
    src/QLTokens.cpp
    src/Service.cpp
    src/AuthService.cpp
    src/BundleActivator.cpp
)
target_link_libraries(PocoOSP PUBLIC Poco::Zip Poco::Util Poco::XML)
target_include_directories(PocoOSP
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

add_library(Poco::OSP ALIAS PocoOSP)
