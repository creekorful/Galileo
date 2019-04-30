cmake_minimum_required(VERSION 3.14)
project(Galileo)

set(CMAKE_CXX_STANDARD 17)

# Here find librairies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Galileo main.cpp Source/Graphics/Window.cpp Source/Graphics/Window.h)

# link librairies
target_link_libraries(Galileo glfw)
target_link_libraries(Galileo ${OPENGL_gl_LIBRARY})