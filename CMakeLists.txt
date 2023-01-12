cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(ZeekPluginCommunityID)

# Establish version numbers in config.h
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION LIMIT_COUNT 1)

string(REGEX REPLACE "[.-]" " " version_numbers ${VERSION})
separate_arguments(version_numbers)
list(GET version_numbers 0 VERSION_MAJOR)
list(GET version_numbers 1 VERSION_MINOR)
list(GET version_numbers 2 VERSION_PATCH)
add_compile_definitions(
    VERSION_MAJOR=${VERSION_MAJOR}
    VERSION_MINOR=${VERSION_MINOR}
    VERSION_PATCH=${VERSION_PATCH})

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
