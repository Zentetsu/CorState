# Install script for directory: /home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/zentetsu/miniconda3/envs/PhD")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS)
  set(CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS "OWNER_READ;OWNER_WRITE;OWNER_EXECUTE;GROUP_READ;GROUP_EXECUTE;WORLD_READ;WORLD_EXECUTE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so.5.4.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so.5"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/zentetsu/Documents/GIT/CorState/build/lib/libjson-c.so.5.4.0"
    "/home/zentetsu/Documents/GIT/CorState/build/lib/libjson-c.so.5"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so.5.4.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so.5"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/zentetsu/Documents/GIT/CorState/build/lib/libjson-c.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/zentetsu/Documents/GIT/CorState/build/lib/libjson-c.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets.cmake"
         "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/CMakeFiles/Export/c72427da9e5c73ebf6c111c2977a0759/json-c-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c" TYPE FILE FILES "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/CMakeFiles/Export/c72427da9e5c73ebf6c111c2977a0759/json-c-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c" TYPE FILE FILES "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/CMakeFiles/Export/c72427da9e5c73ebf6c111c2977a0759/json-c-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c" TYPE FILE FILES "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/json-c-config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/json-c.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_config.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/arraylist.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/debug.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_c_version.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_inttypes.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_object.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_object_iterator.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_tokener.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_types.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_util.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_visit.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/linkhash.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/printbuf.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_pointer.h;/home/zentetsu/miniconda3/envs/PhD/include/json-c/json_patch.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/zentetsu/miniconda3/envs/PhD/include/json-c" TYPE FILE FILES
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/json_config.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/json.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/arraylist.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/debug.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_c_version.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_inttypes.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_object.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_object_iterator.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_tokener.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_types.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_util.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_visit.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/linkhash.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/printbuf.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_pointer.h"
    "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src/json_patch.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/doc/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
