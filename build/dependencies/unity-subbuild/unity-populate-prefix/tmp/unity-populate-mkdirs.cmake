# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/zentetsu/Documents/GIT/CorState/build/dependencies/Unity/src")
  file(MAKE_DIRECTORY "/home/zentetsu/Documents/GIT/CorState/build/dependencies/Unity/src")
endif()
file(MAKE_DIRECTORY
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/Unity/build"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix/tmp"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix/src"
  "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/zentetsu/Documents/GIT/CorState/build/dependencies/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
