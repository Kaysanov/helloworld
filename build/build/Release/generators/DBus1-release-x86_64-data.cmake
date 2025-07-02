########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(dbus_COMPONENT_NAMES "")
if(DEFINED dbus_FIND_DEPENDENCY_NAMES)
  list(APPEND dbus_FIND_DEPENDENCY_NAMES expat)
  list(REMOVE_DUPLICATES dbus_FIND_DEPENDENCY_NAMES)
else()
  set(dbus_FIND_DEPENDENCY_NAMES expat)
endif()
set(expat_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(dbus_PACKAGE_FOLDER_RELEASE "/home/sas/.conan2/p/dbusa4cced2702ecd/p")
set(dbus_BUILD_MODULES_PATHS_RELEASE )


set(dbus_INCLUDE_DIRS_RELEASE )
set(dbus_RES_DIRS_RELEASE "${dbus_PACKAGE_FOLDER_RELEASE}/res")
set(dbus_DEFINITIONS_RELEASE "-DDBUS_STATIC_BUILD")
set(dbus_SHARED_LINK_FLAGS_RELEASE )
set(dbus_EXE_LINK_FLAGS_RELEASE )
set(dbus_OBJECTS_RELEASE )
set(dbus_COMPILE_DEFINITIONS_RELEASE "DBUS_STATIC_BUILD")
set(dbus_COMPILE_OPTIONS_C_RELEASE )
set(dbus_COMPILE_OPTIONS_CXX_RELEASE )
set(dbus_LIB_DIRS_RELEASE "${dbus_PACKAGE_FOLDER_RELEASE}/lib")
set(dbus_BIN_DIRS_RELEASE )
set(dbus_LIBRARY_TYPE_RELEASE STATIC)
set(dbus_IS_HOST_WINDOWS_RELEASE 0)
set(dbus_LIBS_RELEASE dbus-1)
set(dbus_SYSTEM_LIBS_RELEASE rt pthread)
set(dbus_FRAMEWORK_DIRS_RELEASE )
set(dbus_FRAMEWORKS_RELEASE )
set(dbus_BUILD_DIRS_RELEASE )
set(dbus_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(dbus_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${dbus_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${dbus_COMPILE_OPTIONS_C_RELEASE}>")
set(dbus_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${dbus_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${dbus_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${dbus_EXE_LINK_FLAGS_RELEASE}>")


set(dbus_COMPONENTS_RELEASE )