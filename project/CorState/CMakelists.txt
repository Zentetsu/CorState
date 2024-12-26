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

target_link_libraries(CorState json-c::json-c)
target_include_directories(CorState PUBLIC ${INCLUDE_DIR})

set_target_properties(CorState PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
    BUILD_WITH_INSTALL_RPATH TRUE
)

# Install the executable
install(TARGETS CorState
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/CorState
)

add_custom_target(install_corstate DEPENDS CorState)