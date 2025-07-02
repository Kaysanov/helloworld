########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND pulseaudio_COMPONENT_NAMES pulseaudio::pulse pulseaudio::pulse-simple)
list(REMOVE_DUPLICATES pulseaudio_COMPONENT_NAMES)
if(DEFINED pulseaudio_FIND_DEPENDENCY_NAMES)
  list(APPEND pulseaudio_FIND_DEPENDENCY_NAMES Iconv xorg)
  list(REMOVE_DUPLICATES pulseaudio_FIND_DEPENDENCY_NAMES)
else()
  set(pulseaudio_FIND_DEPENDENCY_NAMES Iconv xorg)
endif()
set(Iconv_FIND_MODE "NO_MODULE")
set(xorg_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(pulseaudio_PACKAGE_FOLDER_RELEASE "/home/sas/.conan2/p/pulse479518f2e279d/p")
set(pulseaudio_BUILD_MODULES_PATHS_RELEASE )


set(pulseaudio_INCLUDE_DIRS_RELEASE )
set(pulseaudio_RES_DIRS_RELEASE )
set(pulseaudio_DEFINITIONS_RELEASE "-D_REENTRANT")
set(pulseaudio_SHARED_LINK_FLAGS_RELEASE )
set(pulseaudio_EXE_LINK_FLAGS_RELEASE )
set(pulseaudio_OBJECTS_RELEASE )
set(pulseaudio_COMPILE_DEFINITIONS_RELEASE "_REENTRANT")
set(pulseaudio_COMPILE_OPTIONS_C_RELEASE )
set(pulseaudio_COMPILE_OPTIONS_CXX_RELEASE )
set(pulseaudio_LIB_DIRS_RELEASE "${pulseaudio_PACKAGE_FOLDER_RELEASE}/lib"
			"${pulseaudio_PACKAGE_FOLDER_RELEASE}/lib/pulseaudio")
set(pulseaudio_BIN_DIRS_RELEASE "${pulseaudio_PACKAGE_FOLDER_RELEASE}/bin")
set(pulseaudio_LIBRARY_TYPE_RELEASE SHARED)
set(pulseaudio_IS_HOST_WINDOWS_RELEASE 0)
set(pulseaudio_LIBS_RELEASE pulse-simple pulse pulsecommon-17.0)
set(pulseaudio_SYSTEM_LIBS_RELEASE )
set(pulseaudio_FRAMEWORK_DIRS_RELEASE )
set(pulseaudio_FRAMEWORKS_RELEASE )
set(pulseaudio_BUILD_DIRS_RELEASE )
set(pulseaudio_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(pulseaudio_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${pulseaudio_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${pulseaudio_COMPILE_OPTIONS_C_RELEASE}>")
set(pulseaudio_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${pulseaudio_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${pulseaudio_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${pulseaudio_EXE_LINK_FLAGS_RELEASE}>")


set(pulseaudio_COMPONENTS_RELEASE pulseaudio::pulse pulseaudio::pulse-simple)
########### COMPONENT pulseaudio::pulse-simple VARIABLES ############################################

set(pulseaudio_pulseaudio_pulse-simple_INCLUDE_DIRS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_LIB_DIRS_RELEASE "${pulseaudio_PACKAGE_FOLDER_RELEASE}/lib")
set(pulseaudio_pulseaudio_pulse-simple_BIN_DIRS_RELEASE "${pulseaudio_PACKAGE_FOLDER_RELEASE}/bin")
set(pulseaudio_pulseaudio_pulse-simple_LIBRARY_TYPE_RELEASE SHARED)
set(pulseaudio_pulseaudio_pulse-simple_IS_HOST_WINDOWS_RELEASE 0)
set(pulseaudio_pulseaudio_pulse-simple_RES_DIRS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_DEFINITIONS_RELEASE "-D_REENTRANT")
set(pulseaudio_pulseaudio_pulse-simple_OBJECTS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_COMPILE_DEFINITIONS_RELEASE "_REENTRANT")
set(pulseaudio_pulseaudio_pulse-simple_COMPILE_OPTIONS_C_RELEASE "")
set(pulseaudio_pulseaudio_pulse-simple_COMPILE_OPTIONS_CXX_RELEASE "")
set(pulseaudio_pulseaudio_pulse-simple_LIBS_RELEASE pulse-simple)
set(pulseaudio_pulseaudio_pulse-simple_SYSTEM_LIBS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_FRAMEWORK_DIRS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_FRAMEWORKS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_DEPENDENCIES_RELEASE pulseaudio::pulse)
set(pulseaudio_pulseaudio_pulse-simple_SHARED_LINK_FLAGS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_EXE_LINK_FLAGS_RELEASE )
set(pulseaudio_pulseaudio_pulse-simple_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(pulseaudio_pulseaudio_pulse-simple_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${pulseaudio_pulseaudio_pulse-simple_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${pulseaudio_pulseaudio_pulse-simple_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${pulseaudio_pulseaudio_pulse-simple_EXE_LINK_FLAGS_RELEASE}>
)
set(pulseaudio_pulseaudio_pulse-simple_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${pulseaudio_pulseaudio_pulse-simple_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${pulseaudio_pulseaudio_pulse-simple_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT pulseaudio::pulse VARIABLES ############################################

set(pulseaudio_pulseaudio_pulse_INCLUDE_DIRS_RELEASE )
set(pulseaudio_pulseaudio_pulse_LIB_DIRS_RELEASE "${pulseaudio_PACKAGE_FOLDER_RELEASE}/lib"
			"${pulseaudio_PACKAGE_FOLDER_RELEASE}/lib/pulseaudio")
set(pulseaudio_pulseaudio_pulse_BIN_DIRS_RELEASE "${pulseaudio_PACKAGE_FOLDER_RELEASE}/bin")
set(pulseaudio_pulseaudio_pulse_LIBRARY_TYPE_RELEASE SHARED)
set(pulseaudio_pulseaudio_pulse_IS_HOST_WINDOWS_RELEASE 0)
set(pulseaudio_pulseaudio_pulse_RES_DIRS_RELEASE )
set(pulseaudio_pulseaudio_pulse_DEFINITIONS_RELEASE )
set(pulseaudio_pulseaudio_pulse_OBJECTS_RELEASE )
set(pulseaudio_pulseaudio_pulse_COMPILE_DEFINITIONS_RELEASE )
set(pulseaudio_pulseaudio_pulse_COMPILE_OPTIONS_C_RELEASE "")
set(pulseaudio_pulseaudio_pulse_COMPILE_OPTIONS_CXX_RELEASE "")
set(pulseaudio_pulseaudio_pulse_LIBS_RELEASE pulse pulsecommon-17.0)
set(pulseaudio_pulseaudio_pulse_SYSTEM_LIBS_RELEASE )
set(pulseaudio_pulseaudio_pulse_FRAMEWORK_DIRS_RELEASE )
set(pulseaudio_pulseaudio_pulse_FRAMEWORKS_RELEASE )
set(pulseaudio_pulseaudio_pulse_DEPENDENCIES_RELEASE Iconv::Iconv xorg::xorg)
set(pulseaudio_pulseaudio_pulse_SHARED_LINK_FLAGS_RELEASE )
set(pulseaudio_pulseaudio_pulse_EXE_LINK_FLAGS_RELEASE )
set(pulseaudio_pulseaudio_pulse_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(pulseaudio_pulseaudio_pulse_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${pulseaudio_pulseaudio_pulse_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${pulseaudio_pulseaudio_pulse_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${pulseaudio_pulseaudio_pulse_EXE_LINK_FLAGS_RELEASE}>
)
set(pulseaudio_pulseaudio_pulse_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${pulseaudio_pulseaudio_pulse_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${pulseaudio_pulseaudio_pulse_COMPILE_OPTIONS_C_RELEASE}>")