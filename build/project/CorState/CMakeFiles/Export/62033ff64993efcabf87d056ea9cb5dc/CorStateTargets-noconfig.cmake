#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CorState::CorState" for configuration ""
set_property(TARGET CorState::CorState APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(CorState::CorState PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libCorState.so"
  IMPORTED_SONAME_NOCONFIG "libCorState.so"
  )

list(APPEND _cmake_import_check_targets CorState::CorState )
list(APPEND _cmake_import_check_files_for_CorState::CorState "${_IMPORT_PREFIX}/lib/libCorState.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
