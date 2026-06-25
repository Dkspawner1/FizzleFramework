# Install script for directory: C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/pkgs/spirv-cross_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-c.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-cored.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/GLSL.std.450.h"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_common.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cross_containers.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cross_error_handling.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cross.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_parser.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cross_parsed_ir.hpp"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cfg.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_core/cmake/spirv_cross_coreConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_core/cmake/spirv_cross_coreConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/c867e332942f9fbfd00502e244840eeb/spirv_cross_coreConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_core/cmake/spirv_cross_coreConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_core/cmake/spirv_cross_coreConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_core/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/c867e332942f9fbfd00502e244840eeb/spirv_cross_coreConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_core/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/c867e332942f9fbfd00502e244840eeb/spirv_cross_coreConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-glsld.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_glsl.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_glsl/cmake/spirv_cross_glslConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_glsl/cmake/spirv_cross_glslConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/e2b605c21150436e2d28319122566e16/spirv_cross_glslConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_glsl/cmake/spirv_cross_glslConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_glsl/cmake/spirv_cross_glslConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_glsl/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/e2b605c21150436e2d28319122566e16/spirv_cross_glslConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_glsl/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/e2b605c21150436e2d28319122566e16/spirv_cross_glslConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-cppd.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cpp.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_cpp/cmake/spirv_cross_cppConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_cpp/cmake/spirv_cross_cppConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/e4e8b47b5dea7a8da80c394f3d708597/spirv_cross_cppConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_cpp/cmake/spirv_cross_cppConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_cpp/cmake/spirv_cross_cppConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_cpp/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/e4e8b47b5dea7a8da80c394f3d708597/spirv_cross_cppConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_cpp/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/e4e8b47b5dea7a8da80c394f3d708597/spirv_cross_cppConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-reflectd.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_reflect.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_reflect/cmake/spirv_cross_reflectConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_reflect/cmake/spirv_cross_reflectConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/53f8cf94f22a1f78c96b8f281c6786ac/spirv_cross_reflectConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_reflect/cmake/spirv_cross_reflectConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_reflect/cmake/spirv_cross_reflectConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_reflect/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/53f8cf94f22a1f78c96b8f281c6786ac/spirv_cross_reflectConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_reflect/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/53f8cf94f22a1f78c96b8f281c6786ac/spirv_cross_reflectConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-msld.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_msl.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_msl/cmake/spirv_cross_mslConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_msl/cmake/spirv_cross_mslConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/ce35db60f39fa04fd857e126f4dc3123/spirv_cross_mslConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_msl/cmake/spirv_cross_mslConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_msl/cmake/spirv_cross_mslConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_msl/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/ce35db60f39fa04fd857e126f4dc3123/spirv_cross_mslConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_msl/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/ce35db60f39fa04fd857e126f4dc3123/spirv_cross_mslConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-hlsld.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_hlsl.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_hlsl/cmake/spirv_cross_hlslConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_hlsl/cmake/spirv_cross_hlslConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/7fc66e572ce2ebd507dfbdc071cfe3b7/spirv_cross_hlslConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_hlsl/cmake/spirv_cross_hlslConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_hlsl/cmake/spirv_cross_hlslConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_hlsl/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/7fc66e572ce2ebd507dfbdc071cfe3b7/spirv_cross_hlslConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_hlsl/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/7fc66e572ce2ebd507dfbdc071cfe3b7/spirv_cross_hlslConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-utild.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cross_util.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_util/cmake/spirv_cross_utilConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_util/cmake/spirv_cross_utilConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/ec42c177c5387f57cff93cface715bc9/spirv_cross_utilConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_util/cmake/spirv_cross_utilConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_util/cmake/spirv_cross_utilConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_util/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/ec42c177c5387f57cff93cface715bc9/spirv_cross_utilConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_util/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/ec42c177c5387f57cff93cface715bc9/spirv_cross_utilConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross-cd.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv_cross" TYPE FILE FILES
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv.h"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/src/-1.4.350.0-aa70c38bef.clean/spirv_cross_c.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_c/cmake/spirv_cross_cConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_c/cmake/spirv_cross_cConfig.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/5fd2405ca235bfbb625072e4bac10ae3/spirv_cross_cConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_c/cmake/spirv_cross_cConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/spirv_cross_c/cmake/spirv_cross_cConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_c/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/5fd2405ca235bfbb625072e4bac10ae3/spirv_cross_cConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/spirv_cross_c/cmake" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/Export/5fd2405ca235bfbb625072e4bac10ae3/spirv_cross_cConfig-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/spirv-cross.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/CMakeFiles/spirv-cross.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/spirv-cross/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
