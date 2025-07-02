########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(sndio_FIND_QUIETLY)
    set(sndio_MESSAGE_MODE VERBOSE)
else()
    set(sndio_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/module-sndioTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${libsndio_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(sndio_VERSION_STRING "1.9.0")
set(sndio_INCLUDE_DIRS ${libsndio_INCLUDE_DIRS_RELEASE} )
set(sndio_INCLUDE_DIR ${libsndio_INCLUDE_DIRS_RELEASE} )
set(sndio_LIBRARIES ${libsndio_LIBRARIES_RELEASE} )
set(sndio_DEFINITIONS ${libsndio_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${libsndio_BUILD_MODULES_PATHS_RELEASE} )
    message(${sndio_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


include(FindPackageHandleStandardArgs)
set(sndio_FOUND 1)
set(sndio_VERSION "1.9.0")

find_package_handle_standard_args(sndio
                                  REQUIRED_VARS sndio_VERSION
                                  VERSION_VAR sndio_VERSION)
mark_as_advanced(sndio_FOUND sndio_VERSION)

set(sndio_FOUND 1)
set(sndio_VERSION "1.9.0")
mark_as_advanced(sndio_FOUND sndio_VERSION)

