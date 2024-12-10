cmake_minimum_required(VERSION 3.30)
project(FizzleFramework)

set(CMAKE_CXX_STANDARD 23)

# Specify the path to the GLFW installation
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GLFW_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Include directories for GLAD and GLFW
include_directories(${GLFW_INCLUDE_DIR})

# Add the executable
add_executable(FizzleFramework src/source.cpp src/glad.c
        include/Rectangle.h
        include/Game.h
        include/Color.h
        include/Window.h
        include/Renderer.h
        src/Window.cpp
        src/Renderer.cpp
)

# Link libraries
target_link_libraries(FizzleFramework
        ${GLFW_LIBRARY_DIR}/libglfw3.a
        opengl32
        gdi32
        user32
        kernel32
)

# Copy the DLL to the output directory (optional)
add_custom_command(TARGET FizzleFramework POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_LIBRARY_DIR}/glfw3.dll"
        $<TARGET_FILE_DIR:FizzleFramework>)