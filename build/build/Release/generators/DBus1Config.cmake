########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(DBus1_FIND_QUIETLY)
    set(DBus1_MESSAGE_MODE VERBOSE)
else()
    set(DBus1_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/DBus1Targets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${dbus_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(DBus1_VERSION_STRING "1.15.8")
set(DBus1_INCLUDE_DIRS ${dbus_INCLUDE_DIRS_RELEASE} )
set(DBus1_INCLUDE_DIR ${dbus_INCLUDE_DIRS_RELEASE} )
set(DBus1_LIBRARIES ${dbus_LIBRARIES_RELEASE} )
set(DBus1_DEFINITIONS ${dbus_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${dbus_BUILD_MODULES_PATHS_RELEASE} )
    message(${DBus1_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


