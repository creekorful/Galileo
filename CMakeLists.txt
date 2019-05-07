cmake_minimum_required(VERSION 3.14)
project(Galileo)

set(CMAKE_CXX_STANDARD 17)

# Here find librairies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES_FILES
        main.cpp
        Source/Graphics/Core/Window.cpp
        Source/Graphics/Core/Window.h
        Source/Graphics/Shader/Shader.cpp
        Source/Graphics/Shader/Shader.h
        Source/Graphics/Mesh/Mesh.cpp
        Source/Graphics/Mesh/Mesh.h
        Source/IO/Files.cpp
        Source/IO/Files.h
        Source/Common.h
        Source/Math/Matrix4f.cpp
        Source/Math/Matrix4f.h
        Source/Math/BaseMath.cpp
        Source/Math/BaseMath.h
        Source/Math/Vector2.h
        Source/Math/Vector3.h
        Source/GameObject.cpp
        Source/GameObject.h
        Source/Graphics/Mesh/MeshFactory.cpp
        Source/Graphics/Mesh/MeshFactory.h
        Source/Graphics/Shader/ShaderFactory.cpp
        Source/Graphics/Shader/ShaderFactory.h
        Source/Graphics/Texture/Texture.cpp
        Source/Graphics/Texture/Texture.h
        Source/Graphics/Texture/TextureFactory.cpp
        Source/Graphics/Texture/TextureFactory.h
        Source/Graphics/Texture/Loader/TextureLoader.h
        Source/Graphics/Texture/Loader/PngTextureLoader.cpp
        Source/Graphics/Texture/Loader/PngTextureLoader.h
        Source/Logging/LoggerFactory.cpp
        Source/Logging/LoggerFactory.h
        Source/Logging/Logger.cpp
        Source/Logging/Logger.h
        ThirdParty/stb_image.h
        Source/Graphics/Core/Camera.cpp
        Source/Graphics/Core/Camera.h
        Source/Graphics/Mesh/Loader/ObjFileLoader.cpp
        Source/Graphics/Mesh/Loader/ObjFileLoader.h)

add_executable(Galileo ${SOURCES_FILES})

# link librairies
target_link_libraries(Galileo glfw ${OPENGL_gl_LIBRARY})