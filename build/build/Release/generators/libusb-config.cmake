########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(libusb_FIND_QUIETLY)
    set(libusb_MESSAGE_MODE VERBOSE)
else()
    set(libusb_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libusbTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${libusb_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(libusb_VERSION_STRING "1.0.26")
set(libusb_INCLUDE_DIRS ${libusb_INCLUDE_DIRS_RELEASE} )
set(libusb_INCLUDE_DIR ${libusb_INCLUDE_DIRS_RELEASE} )
set(libusb_LIBRARIES ${libusb_LIBRARIES_RELEASE} )
set(libusb_DEFINITIONS ${libusb_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${libusb_BUILD_MODULES_PATHS_RELEASE} )
    message(${libusb_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


