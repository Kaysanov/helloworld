########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libusb_COMPONENT_NAMES "")
if(DEFINED libusb_FIND_DEPENDENCY_NAMES)
  list(APPEND libusb_FIND_DEPENDENCY_NAMES libudev)
  list(REMOVE_DUPLICATES libusb_FIND_DEPENDENCY_NAMES)
else()
  set(libusb_FIND_DEPENDENCY_NAMES libudev)
endif()
set(libudev_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(libusb_PACKAGE_FOLDER_RELEASE "/home/sas/.conan2/p/libus274f2dc6567ac/p")
set(libusb_BUILD_MODULES_PATHS_RELEASE )


set(libusb_INCLUDE_DIRS_RELEASE )
set(libusb_RES_DIRS_RELEASE )
set(libusb_DEFINITIONS_RELEASE )
set(libusb_SHARED_LINK_FLAGS_RELEASE )
set(libusb_EXE_LINK_FLAGS_RELEASE )
set(libusb_OBJECTS_RELEASE )
set(libusb_COMPILE_DEFINITIONS_RELEASE )
set(libusb_COMPILE_OPTIONS_C_RELEASE )
set(libusb_COMPILE_OPTIONS_CXX_RELEASE )
set(libusb_LIB_DIRS_RELEASE "${libusb_PACKAGE_FOLDER_RELEASE}/lib")
set(libusb_BIN_DIRS_RELEASE )
set(libusb_LIBRARY_TYPE_RELEASE STATIC)
set(libusb_IS_HOST_WINDOWS_RELEASE 0)
set(libusb_LIBS_RELEASE usb-1.0)
set(libusb_SYSTEM_LIBS_RELEASE pthread)
set(libusb_FRAMEWORK_DIRS_RELEASE )
set(libusb_FRAMEWORKS_RELEASE )
set(libusb_BUILD_DIRS_RELEASE )
set(libusb_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libusb_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libusb_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libusb_COMPILE_OPTIONS_C_RELEASE}>")
set(libusb_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libusb_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libusb_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libusb_EXE_LINK_FLAGS_RELEASE}>")


set(libusb_COMPONENTS_RELEASE )