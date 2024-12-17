cmake_minimum_required(VERSION 3.30)
project(FizzleFramework)

set(CMAKE_CXX_STANDARD 23)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Add GLAD
add_library(glad STATIC External/glad/glad.c)
target_include_directories(glad PUBLIC External)

# Add stb_image
include_directories(External/stb)

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
        include/Content/Texture.h
        src/Content/Texture.cpp
        include/Threading/Job.h
        include/Threading/JobSystem.h
        src/Threading/JobSystem.cpp
        include/Scenes/LoadingScene.h
        include/Scenes/Scene.h
        include/Scenes/MenuScene.h
        include/Scenes/GameScene.h
        include/Scenes/SceneManager.h
        src/Scenes/SceneManager.cpp
        src/Scenes/GameScene.cpp
        src/Scenes/MenuScene.cpp
        src/Scenes/LoadingScene.cpp
)

# Set include directories for the executable target
target_include_directories(FizzleFramework PRIVATE include)

# Link libraries based on the operating system
if(WIN32)
    # Windows-specific libraries
    target_link_libraries(FizzleFramework PRIVATE
            glfw
            glad
            opengl32
            gdi32
            user32
            kernel32)
elseif(UNIX)
    # Linux-specific libraries (adjust as necessary)
    target_link_libraries(FizzleFramework PRIVATE
            glfw
            glad
            GL) # Link against libGL on Linux (no need for gdi32, user32, kernel32)
endif()
