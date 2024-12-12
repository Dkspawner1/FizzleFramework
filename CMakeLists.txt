cmake_minimum_required(VERSION 3.30)
project(FizzleFramework)

set(CMAKE_CXX_STANDARD 23)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Add GLAD
add_library(glad STATIC External/glad/glad.c)
target_include_directories(glad PUBLIC External)

# Add the executable
add_executable(FizzleFramework
        src/Game/source.cpp
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
        src/Graphics/GraphicsDeviceManager.cpp
        src/Content/ContentManager.cpp
        src/Graphics/SpriteBatch.cpp
        include/Content/Asset.h
        include/Content/TypedAsset.h
        include/Core/InputManager.h
        src/Core/InputManager.cpp
)

# Set include directories
target_include_directories(FizzleFramework PRIVATE include)

# Link libraries
target_link_libraries(FizzleFramework PRIVATE
        glfw
        glad
        opengl32
        gdi32
        user32
        kernel32
)
