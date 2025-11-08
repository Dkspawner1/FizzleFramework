cmake_minimum_required(VERSION 3.25)
project(FizzleFramework VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# ==============================================================================
# SOURCES & LIBRARIES
# ==============================================================================
file(GLOB_RECURSE SOURCES "src/*.c")
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(PNG REQUIRED)

add_executable(${PROJECT_NAME} source.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image PNG::PNG)

# ==============================================================================
# COMPILER FLAGS
# ==============================================================================
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:/Od;/Zi>")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Release>:/O2;/DNDEBUG>")
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:-O0;-g;-DDEBUG>")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Release>:-O3;-DNDEBUG>")
endif ()

# ==============================================================================
# ASSET PATH - Bake into executable for absolute paths (build directory)
# ==============================================================================
add_compile_definitions(ASSETS_DIR="${CMAKE_BINARY_DIR}/assets")

# ==============================================================================
# ASSET COPYING - Copy from source to build directory
# ==============================================================================
if (EXISTS ${CMAKE_SOURCE_DIR}/assets)
    add_custom_target(copy_assets ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_BINARY_DIR}/assets
            COMMENT "📦 Copying assets to build directory..."
    )
    add_dependencies(${PROJECT_NAME} copy_assets)
    message(STATUS "✅ Assets will be copied to: ${CMAKE_BINARY_DIR}/assets")
else ()
    message(FATAL_ERROR "❌ No assets folder found at ${CMAKE_SOURCE_DIR}/assets")
endif ()

# ==============================================================================
# DEPENDENCY DLL COPYING FOR WINDOWS
# ==============================================================================
if (WIN32)
    # Get library locations
    get_target_property(SDL3_LOCATION SDL3::SDL3 IMPORTED_LOCATION_RELEASE)
    if (NOT SDL3_LOCATION)
        get_target_property(SDL3_LOCATION SDL3::SDL3 IMPORTED_LOCATION)
    endif ()

    get_target_property(SDL3_IMAGE_LOCATION SDL3_image::SDL3_image IMPORTED_LOCATION_RELEASE)
    if (NOT SDL3_IMAGE_LOCATION)
        get_target_property(SDL3_IMAGE_LOCATION SDL3_image::SDL3_image IMPORTED_LOCATION)
    endif ()

    # Copy main SDL3 DLLs
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_LOCATION}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3.dll"
            COMMENT "📦 Copying SDL3.dll..."
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_IMAGE_LOCATION}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3_image.dll"
            COMMENT "📦 Copying SDL3_image.dll..."
    )

    # Copy dependencies from MSYS2
    set(MSYS2_BIN "C:/msys64/ucrt64/bin")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_BIN}/libpng16-16.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/libpng16-16.dll"
            COMMENT "📦 Copying libpng16-16.dll..."
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSYS2_BIN}/zlib1.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/zlib1.dll"
            COMMENT "📦 Copying zlib1.dll..."
    )

    message(STATUS "✅ DLL copying enabled for Windows")
endif ()

# ==============================================================================
# BUILD INFO
# ==============================================================================
message(STATUS "")
message(STATUS "🎮 FizzleFramework Configuration")
message(STATUS "   Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "   C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "   Generator: ${CMAKE_GENERATOR}")
message(STATUS "")
