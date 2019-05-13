cmake_minimum_required(VERSION 3.14)
project(Galileo)

set(CMAKE_CXX_STANDARD 17)

# Here find librairies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES_FILES
        Source/Game/main.cpp
        Source/Engine/Core/Window.cpp
        Source/Engine/Core/Window.h
        Source/Engine/Graphics/Shader/Shader.cpp
        Source/Engine/Graphics/Shader/Shader.h
        Source/Engine/Graphics/Mesh/Mesh.cpp
        Source/Engine/Graphics/Mesh/Mesh.h
        Source/Engine/IO/Files.cpp
        Source/Engine/IO/Files.h
        Source/Engine/Common.h
        Source/Engine/Math/Matrix4f.cpp
        Source/Engine/Math/Matrix4f.h
        Source/Engine/Math/BaseMath.cpp
        Source/Engine/Math/BaseMath.h
        Source/Engine/Math/Vector2.h
        Source/Engine/Math/Vector3.h
        Source/Engine/Core/GameObject.cpp
        Source/Engine/Core/GameObject.h
        Source/Engine/Graphics/Mesh/MeshFactory.cpp
        Source/Engine/Graphics/Mesh/MeshFactory.h
        Source/Engine/Graphics/Shader/ShaderFactory.cpp
        Source/Engine/Graphics/Shader/ShaderFactory.h
        Source/Engine/Graphics/Texture/Texture.cpp
        Source/Engine/Graphics/Texture/Texture.h
        Source/Engine/Graphics/Texture/TextureFactory.cpp
        Source/Engine/Graphics/Texture/TextureFactory.h
        Source/Engine/Graphics/Texture/Loader/TextureLoader.h
        Source/Engine/Graphics/Texture/Loader/PngTextureLoader.cpp
        Source/Engine/Graphics/Texture/Loader/PngTextureLoader.h
        Source/Engine/Logging/LoggerFactory.cpp
        Source/Engine/Logging/LoggerFactory.h
        Source/Engine/Logging/Logger.cpp
        Source/Engine/Logging/Logger.h
        Source/Engine/ThirdParty/stb_image.h
        Source/Engine/ThirdParty/stb_perlin.h
        Source/Engine/Graphics/Mesh/Loader/ObjFileLoader.cpp
        Source/Engine/Graphics/Mesh/Loader/ObjFileLoader.h
        Source/Engine/Util/Strings.cpp
        Source/Engine/Util/Strings.h
        Source/Engine/Core/Camera.cpp
        Source/Engine/Core/Camera.h
        Source/Engine/Core/GameEngine.cpp
        Source/Engine/Core/GameEngine.h
        Source/Engine/Core/GameState.h
        Source/Game/MyGameState.cpp
        Source/Game/MyGameState.h
        Source/Engine/Core/Component.h Source/Game/KeyboardController.cpp Source/Game/KeyboardController.h)

add_executable(Galileo ${SOURCES_FILES})

# link librairies
target_link_libraries(Galileo glfw ${OPENGL_gl_LIBRARY})