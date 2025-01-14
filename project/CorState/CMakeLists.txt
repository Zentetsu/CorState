cmake_minimum_required(VERSION 3.11)

# Define folders
set(SRC_DIR ${CMAKE_SOURCE_DIR}/project/CorState/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/project/CorState/include)

# CorState files
set(CorState_HEADER
    ${INCLUDE_DIR}/CorState.h
    ${INCLUDE_DIR}/genericList.h
    ${INCLUDE_DIR}/dictionary.h
    ${INCLUDE_DIR}/stateMachine.h
    ${INCLUDE_DIR}/state.h
    ${INCLUDE_DIR}/transition.h
    ${INCLUDE_DIR}/dataType.h
)

set(CorState_SOURCE
    ${SRC_DIR}/genericList.c
    ${SRC_DIR}/dictionary.c
    ${SRC_DIR}/stateMachine.c
    ${SRC_DIR}/state.c
    ${SRC_DIR}/transition.c
    ${SRC_DIR}/dataType.c
)

# Define the executable
add_library(CorState SHARED ${CorState_HEADER} ${CorState_SOURCE})

set_target_properties(CorState PROPERTIES
    PUBLIC_HEADER "${CorState_HEADER}"
)

target_link_libraries(CorState PUBLIC json-c::json-c)

# target_include_directories(CorState PUBLIC ${INCLUDE_DIR})
target_include_directories(CorState PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(CorState PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
    BUILD_WITH_INSTALL_RPATH TRUE
)

# Install the executable
install(TARGETS CorState
    EXPORT CorStateTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/CorState
)

# Export the targets to a file
install(EXPORT CorStateTargets
    FILE CorStateTargets.cmake
    NAMESPACE CorState::
    DESTINATION lib/cmake/CorState
)

# Generate the Config.cmake file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/CorStateConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CorStateConfig.cmake
    INSTALL_DESTINATION lib/cmake/CorState
)

# Install the Config.cmake file
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/CorStateConfig.cmake
    DESTINATION lib/cmake/CorState
)

add_custom_target(install_corstate DEPENDS CorState)