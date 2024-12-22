cmake_minimum_required(VERSION 3.30)
project(FizzleFramework)

set(CMAKE_CXX_STANDARD 23)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Add FreeType
set(FREETYPE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/External/freetype")
set(FREETYPE_LIBRARY "${CMAKE_SOURCE_DIR}/lib/freetype.lib")

if(NOT EXISTS ${FREETYPE_LIBRARY})
    message(FATAL_ERROR "FreeType library not found at ${FREETYPE_LIBRARY}")
endif()

# Add GLAD
add_library(glad STATIC External/glad/glad.c)
target_include_directories(glad PUBLIC External)

# Add stb_image
include_directories(External/stb)

# Add all source files
file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/*.c"
)

# Add all header files
file(GLOB_RECURSE HEADER_FILES
        "include/*.h"
)

# Add the executable
add_executable(FizzleFramework
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

# Set include directories for the executable target
target_include_directories(FizzleFramework PRIVATE
        include
        ${FREETYPE_INCLUDE_DIRS}
        External
)

# Link libraries based on the operating system
if(WIN32)
    target_link_libraries(FizzleFramework PRIVATE
            glfw
            glad
            opengl32
            gdi32
            user32
            kernel32
            ${FREETYPE_LIBRARY}
    )
elseif(UNIX)
    target_link_libraries(FizzleFramework PRIVATE
            glfw
            glad
            GL
            ${FREETYPE_LIBRARY}
    )
endif()

# Copy DLLs to output directory
add_custom_command(TARGET FizzleFramework POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/glfw3.dll"
        "${CMAKE_SOURCE_DIR}/lib/freetype.dll"
        $<TARGET_FILE_DIR:FizzleFramework>
)