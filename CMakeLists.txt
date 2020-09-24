
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(ZeekPluginCommunityID)

include(MacDependencyPaths)
find_package(OpenSSL REQUIRED)
include_directories(BEFORE ${OPENSSL_INCLUDE_DIR})

include(ZeekPlugin)

zeek_plugin_begin(Corelight CommunityID)
zeek_plugin_cc(src/Plugin.cc)
zeek_plugin_bif(src/communityid.bif)
zeek_plugin_dist_files(README COPYING VERSION)
zeek_plugin_end()

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION LIMIT_COUNT 1)

if ("${BRO_HAS_OLD_DIGEST_CODE}")
   add_definitions(-DBRO_HAS_OLD_DIGEST_CODE)
endif ()

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    # Allows building rpm/deb packages via "make package" in build dir.
    include(ConfigurePackaging)
    ConfigurePackaging(${VERSION})
endif ()
