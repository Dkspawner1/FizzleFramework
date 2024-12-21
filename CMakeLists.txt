cmake_minimum_required(VERSION 3.12)
project(FizzleFramework)

set(CMAKE_CXX_STANDARD 23)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Find FreeType package
find_package(Freetype REQUIRED)

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

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(FizzleFramework PRIVATE
        glfw
        glad
        ${OPENGL_LIBRARIES}
        Freetype::Freetype
)

# Platform-specific configurations
if(WIN32)
    target_link_libraries(FizzleFramework PRIVATE
            gdi32
            user32
            kernel32
    )
elseif(UNIX AND NOT APPLE)
    target_link_libraries(FizzleFramework PRIVATE
            dl
            pthread
    )
endif()

# Copy DLLs to output directory (Windows only)
if(WIN32)
    add_custom_command(TARGET FizzleFramework POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/lib/glfw3.dll"
            $<TARGET_FILE_DIR:FizzleFramework>
    )
endif()
