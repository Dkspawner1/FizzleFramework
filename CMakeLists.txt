cmake_minimum_required(VERSION 3.25)

project(FizzleFramework CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# ── SDL3 + SDL_shadercross (both via vcpkg) ───────────────────────────────────
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_shadercross CONFIG REQUIRED)

# ── Sources ───────────────────────────────────────────────────────────────────
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.cxx"
    "include/*.h"
    "include/*.hpp"
)

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found under src/ or include/.")
endif()

add_executable(FizzleFramework ${SOURCES})

# ── Include dirs ──────────────────────────────────────────────────────────────
target_include_directories(FizzleFramework PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# ── Link ──────────────────────────────────────────────────────────────────────
target_link_libraries(FizzleFramework PRIVATE
    SDL3::SDL3
    SDL3_shadercross::SDL3_shadercross
)

if(WIN32)
    target_link_libraries(FizzleFramework PRIVATE winmm imm32 version setupapi)
endif()

# ── Compiler options ──────────────────────────────────────────────────────────
if(MSVC)
    target_compile_options(FizzleFramework PRIVATE
        /W4
        /WX-
        /wd4100
        /utf-8
        /permissive-
        /Zc:preprocessor
        $<$<CONFIG:Debug>:/Od /RTC1 /Zi>
        $<$<CONFIG:Release>:/O2 /GL /DNDEBUG>
        $<$<CONFIG:RelWithDebInfo>:/O2 /Zi /DNDEBUG>
    )
    target_link_options(FizzleFramework PRIVATE
        $<$<CONFIG:Release>:/LTCG>
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(FizzleFramework PRIVATE
        -Wall -Wextra -Wpedantic -Wno-unused-parameter
        $<$<CONFIG:Debug>:-g3 -fno-omit-frame-pointer>
        $<$<CONFIG:Release>:-O2 -DNDEBUG>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g -DNDEBUG>
    )
endif()

# ── Shader compilation ────────────────────────────────────────────────────────
# Source:   {ProjectRoot}/assets/shaders/src/<group>_<stage>.glsl
# Compiled: {ProjectRoot}/assets/shaders/compiled/spirv/<group>/<name>.spv
# Only .spv files are copied to the binary output dir — raw sources never touched.
#
# Stage inferred from last underscore segment:
#   _vertex → vert  |  _fragment → frag  |  _compute → comp
#   _geometry → geom  |  _tesc → tesc  |  _tese → tese

set(SHADER_SRC_DIR   "${CMAKE_SOURCE_DIR}/assets/shaders/src")
set(SHADER_SPIRV_DIR "${CMAKE_SOURCE_DIR}/assets/shaders/compiled/spirv")

file(MAKE_DIRECTORY "${SHADER_SPIRV_DIR}")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/shaders/compiled/msl")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/shaders/compiled/dxil")

find_program(GLSLANG_VALIDATOR
    NAMES glslangValidator glslangValidator.exe
    HINTS "$ENV{VULKAN_SDK}/Bin" "$ENV{VK_SDK_PATH}/Bin"
    DOC "glslangValidator from the Vulkan SDK"
)

if(GLSLANG_VALIDATOR)
    message(STATUS "Shader compiler: ${GLSLANG_VALIDATOR}")

    file(GLOB_RECURSE SHADER_SOURCES CONFIGURE_DEPENDS
        "${SHADER_SRC_DIR}/*.glsl"
        "${SHADER_SRC_DIR}/*.vert"
        "${SHADER_SRC_DIR}/*.frag"
        "${SHADER_SRC_DIR}/*.comp"
    )

    set(SPIRV_OUTPUTS "")

    foreach(SHADER_FILE IN LISTS SHADER_SOURCES)
        get_filename_component(SHADER_NAME "${SHADER_FILE}" NAME_WE)
        string(REGEX REPLACE "_[^_]+$" "" SHADER_GROUP "${SHADER_NAME}")
        string(REGEX MATCH   "[^_]+$"  SHADER_STAGE_WORD "${SHADER_NAME}")

        if("${SHADER_STAGE_WORD}" STREQUAL "vertex")
            set(GLSL_STAGE "vert")
        elseif("${SHADER_STAGE_WORD}" STREQUAL "fragment")
            set(GLSL_STAGE "frag")
        elseif("${SHADER_STAGE_WORD}" STREQUAL "compute")
            set(GLSL_STAGE "comp")
        elseif("${SHADER_STAGE_WORD}" STREQUAL "geometry")
            set(GLSL_STAGE "geom")
        elseif("${SHADER_STAGE_WORD}" STREQUAL "tesc")
            set(GLSL_STAGE "tesc")
        elseif("${SHADER_STAGE_WORD}" STREQUAL "tese")
            set(GLSL_STAGE "tese")
        else()
            set(GLSL_STAGE "")
        endif()

        set(SPV_OUT_DIR  "${SHADER_SPIRV_DIR}/${SHADER_GROUP}")
        set(SPV_OUT_FILE "${SPV_OUT_DIR}/${SHADER_NAME}.spv")
        file(MAKE_DIRECTORY "${SPV_OUT_DIR}")

        if(GLSL_STAGE)
            set(STAGE_ARG -S ${GLSL_STAGE})
        else()
            set(STAGE_ARG "")
        endif()

        add_custom_command(
            OUTPUT  "${SPV_OUT_FILE}"
            COMMAND "${GLSLANG_VALIDATOR}" -V ${STAGE_ARG} "${SHADER_FILE}" -o "${SPV_OUT_FILE}"
            DEPENDS "${SHADER_FILE}"
            COMMENT "GLSL->SPIR-V: ${SHADER_NAME}"
            VERBATIM
        )

        list(APPEND SPIRV_OUTPUTS "${SPV_OUT_FILE}")
    endforeach()

    if(SPIRV_OUTPUTS)
        add_custom_target(compile_shaders ALL DEPENDS ${SPIRV_OUTPUTS})
        add_dependencies(FizzleFramework compile_shaders)

        add_custom_command(TARGET compile_shaders POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/assets/shaders/compiled"
                "$<TARGET_FILE_DIR:FizzleFramework>/assets/shaders/compiled"
            COMMENT "Copying compiled shaders to output dir"
            VERBATIM
        )
    else()
        message(STATUS "No shaders found in ${SHADER_SRC_DIR} - add .glsl files to enable compilation.")
    endif()
else()
    message(WARNING "glslangValidator not found - shaders will not compile. Set VULKAN_SDK env var.")
endif()

# ── Build info ────────────────────────────────────────────────────────────────
message(STATUS "")
message(STATUS "=== FizzleFramework ===")
message(STATUS "  Build type : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler   : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Shader src : ${SHADER_SRC_DIR}")
message(STATUS "=======================")
message(STATUS "")