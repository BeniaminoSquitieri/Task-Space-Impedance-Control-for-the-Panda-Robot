#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kdl_inverse_dynamics_solver::kdl_inverse_dynamics_solver" for configuration ""
set_property(TARGET kdl_inverse_dynamics_solver::kdl_inverse_dynamics_solver APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(kdl_inverse_dynamics_solver::kdl_inverse_dynamics_solver PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libkdl_inverse_dynamics_solver.so"
  IMPORTED_SONAME_NOCONFIG "libkdl_inverse_dynamics_solver.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS kdl_inverse_dynamics_solver::kdl_inverse_dynamics_solver )
list(APPEND _IMPORT_CHECK_FILES_FOR_kdl_inverse_dynamics_solver::kdl_inverse_dynamics_solver "${_IMPORT_PREFIX}/lib/libkdl_inverse_dynamics_solver.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
