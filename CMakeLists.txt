cmake_minimum_required(VERSION 3.30)
project(FizzleFramework)

set(CMAKE_CXX_STANDARD 23)

# Specify the path to the GLFW installation
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GLFW_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Include directories for GLAD and GLFW
include_directories(${GLFW_INCLUDE_DIR})

# Add the executable
add_executable(FizzleFramework src/Game/source.cpp src/glad.c
        include/Core/Rectangle.h
        include/Core/Game.h
        include/Graphics/Color.h
        include/Graphics/Window.h
        include/Graphics/Renderer.h
        src/Graphics/Window.cpp
        src/Graphics/Renderer.cpp
        include/Core/GameTime.h
        src/Core/GameTime.cpp
        src/Core/Game.cpp
        include/Game/Game1.h
        include/Graphics/GraphicsDeviceManager.h
        include/Content/ContentManager.h
        include/Graphics/SpriteBatch.h
        src/Game/Game1.cpp
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