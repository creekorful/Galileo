cmake_minimum_required(VERSION 3.14)
project(Galileo)

set(CMAKE_CXX_STANDARD 17)

# Here find librairies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES_FILES
        main.cpp
        Source/Graphics/Window.cpp
        Source/Graphics/Window.h
        Source/Graphics/Shader.cpp
        Source/Graphics/Shader.h
        Source/Graphics/Mesh.cpp
        Source/Graphics/Mesh.h
        Source/IO/Files.cpp
        Source/IO/Files.h
        Source/Common.h
        Source/Math/Matrix4f.cpp
        Source/Math/Matrix4f.h
        Source/Math/BaseMath.cpp
        Source/Math/BaseMath.h
        Source/Math/Vector2.h
        Source/Math/Vector2i.cpp
        Source/Math/Vector2i.h
        Source/Math/Vector3.h
        Source/Math/Vector3f.cpp
        Source/Math/Vector3f.h
        Source/GameObject.cpp
        Source/GameObject.h)

add_executable(Galileo ${SOURCES_FILES})

# link librairies
target_link_libraries(Galileo glfw ${OPENGL_gl_LIBRARY})