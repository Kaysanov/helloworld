########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libsndio_COMPONENT_NAMES "")
if(DEFINED libsndio_FIND_DEPENDENCY_NAMES)
  list(APPEND libsndio_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES libsndio_FIND_DEPENDENCY_NAMES)
else()
  set(libsndio_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(libsndio_PACKAGE_FOLDER_RELEASE "/home/sas/.conan2/p/libsnf7a6f70f3f936/p")
set(libsndio_BUILD_MODULES_PATHS_RELEASE )


set(libsndio_INCLUDE_DIRS_RELEASE )
set(libsndio_RES_DIRS_RELEASE )
set(libsndio_DEFINITIONS_RELEASE )
set(libsndio_SHARED_LINK_FLAGS_RELEASE )
set(libsndio_EXE_LINK_FLAGS_RELEASE )
set(libsndio_OBJECTS_RELEASE )
set(libsndio_COMPILE_DEFINITIONS_RELEASE )
set(libsndio_COMPILE_OPTIONS_C_RELEASE )
set(libsndio_COMPILE_OPTIONS_CXX_RELEASE )
set(libsndio_LIB_DIRS_RELEASE "${libsndio_PACKAGE_FOLDER_RELEASE}/lib")
set(libsndio_BIN_DIRS_RELEASE "${libsndio_PACKAGE_FOLDER_RELEASE}/bin")
set(libsndio_LIBRARY_TYPE_RELEASE SHARED)
set(libsndio_IS_HOST_WINDOWS_RELEASE 0)
set(libsndio_LIBS_RELEASE sndio)
set(libsndio_SYSTEM_LIBS_RELEASE dl m rt)
set(libsndio_FRAMEWORK_DIRS_RELEASE )
set(libsndio_FRAMEWORKS_RELEASE )
set(libsndio_BUILD_DIRS_RELEASE )
set(libsndio_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libsndio_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libsndio_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libsndio_COMPILE_OPTIONS_C_RELEASE}>")
set(libsndio_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libsndio_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libsndio_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libsndio_EXE_LINK_FLAGS_RELEASE}>")


set(libsndio_COMPONENTS_RELEASE )