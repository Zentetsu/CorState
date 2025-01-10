cmake_minimum_required(VERSION 3.11)

# Fetch json-c from GitHub
include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/dependencies)
FetchContent_Declare(
    json-c
    GIT_REPOSITORY https://github.com/json-c/json-c.git
    GIT_TAG master
    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/json-c/src
    BINARY_DIR ${FETCHCONTENT_BASE_DIR}/json-c/build
)

set(JSONC_CMAKE_ARGS
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

FetchContent_MakeAvailable(json-c)

if(NOT TARGET json-c::json-c)
    add_library(json-c::json-c ALIAS json-c)
endif()

add_custom_target(install_jsonc DEPENDS json-c)

# Fetch Unity from GitHub
FetchContent_Declare(
    Unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG master
    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/Unity/src
    BINARY_DIR ${FETCHCONTENT_BASE_DIR}/Unity/build
)

set(UNITY_CMAKE_ARGS
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

FetchContent_MakeAvailable(Unity)

if(NOT TARGET unity)
    add_library(unity ALIAS Unity)
endif()

add_custom_target(install_unity DEPENDS Unity)