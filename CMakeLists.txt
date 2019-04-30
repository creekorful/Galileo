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
        )

add_executable(Galileo ${SOURCES_FILES})

# link librairies
target_link_libraries(Galileo glfw)
target_link_libraries(Galileo ${OPENGL_gl_LIBRARY})