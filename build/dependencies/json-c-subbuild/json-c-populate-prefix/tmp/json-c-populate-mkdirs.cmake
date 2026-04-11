# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src")
  file(MAKE_DIRECTORY "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/src")
endif()
file(MAKE_DIRECTORY
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c/build"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix/tmp"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix/src/json-c-populate-stamp"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix/src"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix/src/json-c-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix/src/json-c-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/zentetsu/Documents/GIT/CorState/build/dependencies/json-c-subbuild/json-c-populate-prefix/src/json-c-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
