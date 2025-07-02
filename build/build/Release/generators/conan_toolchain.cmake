# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()
message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()

########## 'user_toolchain' block #############
# Include one or more CMake user toolchain from tools.cmake.cmaketoolchain:user_toolchain



########## 'generic_system' block #############
# Definition of system, platform and toolset





########## 'compilers' block #############



########## 'arch_flags' block #############
# Define C++ flags, C flags and linker flags from 'settings.arch'

message(STATUS "Conan toolchain: Defining architecture flag: -m64")
string(APPEND CONAN_CXX_FLAGS " -m64")
string(APPEND CONAN_C_FLAGS " -m64")
string(APPEND CONAN_SHARED_LINKER_FLAGS " -m64")
string(APPEND CONAN_EXE_LINKER_FLAGS " -m64")


########## 'libcxx' block #############
# Definition of libcxx from 'compiler.libcxx' setting, defining the
# right CXX_FLAGS for that libcxx



########## 'cppstd' block #############
# Define the C++ and C standards from 'compiler.cppstd' and 'compiler.cstd'

function(conan_modify_std_watch variable access value current_list_file stack)
    set(conan_watched_std_variable "17")
    if (${variable} STREQUAL "CMAKE_C_STANDARD")
        set(conan_watched_std_variable "")
    endif()
    if ("${access}" STREQUAL "MODIFIED_ACCESS" AND NOT "${value}" STREQUAL "${conan_watched_std_variable}")
        message(STATUS "Warning: Standard ${variable} value defined in conan_toolchain.cmake to ${conan_watched_std_variable} has been modified to ${value} by ${current_list_file}")
    endif()
    unset(conan_watched_std_variable)
endfunction()

message(STATUS "Conan toolchain: C++ Standard 17 with extensions ON")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
variable_watch(CMAKE_CXX_STANDARD conan_modify_std_watch)


########## 'extra_flags' block #############
# Include extra C++, C and linker flags from configuration tools.build:<type>flags
# and from CMakeToolchain.extra_<type>_flags

# Conan conf flags start: 
# Conan conf flags end


########## 'cmake_flags_init' block #############
# Define CMAKE_<XXX>_FLAGS from CONAN_<XXX>_FLAGS

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


########## 'extra_variables' block #############
# Definition of extra CMake variables from tools.cmake.cmaketoolchain:extra_variables



########## 'try_compile' block #############
# Blocks after this one will not be added when running CMake try/checks

get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()


########## 'find_paths' block #############
# Define paths to find packages, programs, libraries, etc.
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/conan_cmakedeps_paths.cmake")
  message(STATUS "Conan toolchain: Including CMakeDeps generated conan_cmakedeps_paths.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/conan_cmakedeps_paths.cmake")
else()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "/home/sas/.conan2/p/sdl11d5b867f7d1f/p/lib" "/home/sas/.conan2/p/libus274f2dc6567ac/p/lib" "/home/sas/.conan2/p/dbusa4cced2702ecd/p/lib" "/home/sas/.conan2/p/pulse479518f2e279d/p/lib" "/home/sas/.conan2/p/pulse479518f2e279d/p/lib/pulseaudio" "lib" "lib" "lib" "lib" "lib" "lib" "lib" "lib" "lib" "/home/sas/.conan2/p/libal3b7a099ce9ae0/p/lib" "/home/sas/.conan2/p/libsnf7a6f70f3f936/p/lib" "/home/sas/.conan2/p/xkbco75dc371c556ae/p/lib" "/home/sas/.conan2/p/waylab8445dcef3228/p/lib" "/home/sas/.conan2/p/libff68b6f04570036/p/lib" "/home/sas/.conan2/p/libxmb5459b286c0de/p/lib" "/home/sas/.conan2/p/zlib9780dc2008618/p/lib" "/home/sas/.conan2/p/libic39b3eb43cca86/p/lib" "/home/sas/.conan2/p/expat533678a86db61/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "/home/sas/.conan2/p/sdl11d5b867f7d1f/p/include" "/home/sas/.conan2/p/libus274f2dc6567ac/p/include" "/home/sas/.conan2/p/libus274f2dc6567ac/p/include/libusb-1.0" "/home/sas/.conan2/p/dbusa4cced2702ecd/p/include" "/home/sas/.conan2/p/dbusa4cced2702ecd/p/include/dbus-1.0" "/home/sas/.conan2/p/dbusa4cced2702ecd/p/lib/dbus-1.0/include" "/home/sas/.conan2/p/pulse479518f2e279d/p/include" "include" "include" "include" "include" "include" "include" "include" "include" "include" "/home/sas/.conan2/p/libal3b7a099ce9ae0/p/include" "/home/sas/.conan2/p/libsnf7a6f70f3f936/p/include" "/home/sas/.conan2/p/xkbco75dc371c556ae/p/include" "/home/sas/.conan2/p/waylab8445dcef3228/p/include" "/home/sas/.conan2/p/libff68b6f04570036/p/include" "/home/sas/.conan2/p/libxmb5459b286c0de/p/include" "/home/sas/.conan2/p/libxmb5459b286c0de/p/include/libxml2" "/home/sas/.conan2/p/zlib9780dc2008618/p/include" "/home/sas/.conan2/p/libic39b3eb43cca86/p/include" "/home/sas/.conan2/p/expat533678a86db61/p/include")
set(CONAN_RUNTIME_LIB_DIRS "/home/sas/.conan2/p/sdl11d5b867f7d1f/p/lib" "/home/sas/.conan2/p/libus274f2dc6567ac/p/lib" "/home/sas/.conan2/p/dbusa4cced2702ecd/p/lib" "/home/sas/.conan2/p/pulse479518f2e279d/p/lib" "/home/sas/.conan2/p/pulse479518f2e279d/p/lib/pulseaudio" "lib" "lib" "lib" "lib" "lib" "lib" "lib" "lib" "lib" "/home/sas/.conan2/p/libal3b7a099ce9ae0/p/lib" "/home/sas/.conan2/p/libsnf7a6f70f3f936/p/lib" "/home/sas/.conan2/p/xkbco75dc371c556ae/p/lib" "/home/sas/.conan2/p/waylab8445dcef3228/p/lib" "/home/sas/.conan2/p/libff68b6f04570036/p/lib" "/home/sas/.conan2/p/libxmb5459b286c0de/p/lib" "/home/sas/.conan2/p/zlib9780dc2008618/p/lib" "/home/sas/.conan2/p/libic39b3eb43cca86/p/lib" "/home/sas/.conan2/p/expat533678a86db61/p/lib" )

endif()


########## 'pkg_config' block #############
# Define pkg-config from 'tools.gnu:pkg_config' executable and paths

if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR}:$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR}:")
endif()


########## 'rpath' block #############
# Defining CMAKE_SKIP_RPATH



########## 'output_dirs' block #############
# Definition of CMAKE_INSTALL_XXX folders

set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_SBINDIR "bin")
set(CMAKE_INSTALL_LIBEXECDIR "bin")
set(CMAKE_INSTALL_LIBDIR "lib")
set(CMAKE_INSTALL_INCLUDEDIR "include")
set(CMAKE_INSTALL_OLDINCLUDEDIR "include")


########## 'variables' block #############
# Definition of CMake variables from CMakeToolchain.variables values

# Variables
# Variables  per configuration



########## 'preprocessor' block #############
# Preprocessor definitions from CMakeToolchain.preprocessor_definitions values

# Preprocessor definitions per configuration



if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()
