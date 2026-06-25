# Install script for directory: C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/src/467bac3b2e-20f23e0ab4.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/pkgs/sdl3-shadercross_x64-windows/debug")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/SDL3_shadercross.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/SDL3_shadercross.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross/SDL3_shadercross-shared-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross/SDL3_shadercross-shared-targets.cmake"
         "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/CMakeFiles/Export/a722df4dc531c1ca6287d7d5bec44dd4/SDL3_shadercross-shared-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross/SDL3_shadercross-shared-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross/SDL3_shadercross-shared-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/CMakeFiles/Export/a722df4dc531c1ca6287d7d5bec44dd4/SDL3_shadercross-shared-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/CMakeFiles/Export/a722df4dc531c1ca6287d7d5bec44dd4/SDL3_shadercross-shared-targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "DEVEL" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3_shadercross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/src/467bac3b2e-20f23e0ab4.clean/include/SDL3_shadercross/SDL_shadercross.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/shadercross.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross" TYPE FILE FILES
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/SDL3_shadercrossConfig.cmake"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/SDL3_shadercrossConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3_shadercross" TYPE FILE FILES
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/src/467bac3b2e-20f23e0ab4.clean/cmake/sdlcpu.cmake"
    "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/src/467bac3b2e-20f23e0ab4.clean/cmake/FindDirectXShaderCompiler.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/sdl3-shadercross.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL3_shadercross" TYPE FILE FILES "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/src/467bac3b2e-20f23e0ab4.clean/LICENSE.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/install_local_manifest.txt"
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
  file(WRITE "C:/Users/Dorll/source/repos/FizzleFramework/vcpkg_installed/vcpkg/blds/sdl3-shadercross/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
