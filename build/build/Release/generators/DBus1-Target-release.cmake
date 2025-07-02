# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(dbus_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(dbus_FRAMEWORKS_FOUND_RELEASE "${dbus_FRAMEWORKS_RELEASE}" "${dbus_FRAMEWORK_DIRS_RELEASE}")

set(dbus_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET dbus_DEPS_TARGET)
    add_library(dbus_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET dbus_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${dbus_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${dbus_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:expat::expat>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### dbus_DEPS_TARGET to all of them
conan_package_library_targets("${dbus_LIBS_RELEASE}"    # libraries
                              "${dbus_LIB_DIRS_RELEASE}" # package_libdir
                              "${dbus_BIN_DIRS_RELEASE}" # package_bindir
                              "${dbus_LIBRARY_TYPE_RELEASE}"
                              "${dbus_IS_HOST_WINDOWS_RELEASE}"
                              dbus_DEPS_TARGET
                              dbus_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "dbus"    # package_name
                              "${dbus_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${dbus_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET dbus-1
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${dbus_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${dbus_LIBRARIES_TARGETS}>
                 )

    if("${dbus_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET dbus-1
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     dbus_DEPS_TARGET)
    endif()

    set_property(TARGET dbus-1
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${dbus_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET dbus-1
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${dbus_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET dbus-1
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${dbus_LIB_DIRS_RELEASE}>)
    set_property(TARGET dbus-1
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${dbus_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET dbus-1
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${dbus_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(dbus_LIBRARIES_RELEASE dbus-1)
