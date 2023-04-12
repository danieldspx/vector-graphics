FIND_PACKAGE(OpenGL)
cmake_minimum_required(VERSION 3.25)
project(VectorGraphics)

set(CMAKE_CXX_STANDARD 11)

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(
        VectorGraphics
        include/GL/freeglut.h
        include/GL/freeglut_ext.h
        include/GL/freeglut_std.h
        include/GL/glut.h
        src/main.cpp
        src/Bola.h
        src/Botao.h
        src/Relogio.cpp src/Relogio.h
        src/Vector2.h
        src/gl_canvas2d.cpp src/gl_canvas2d.h)

target_link_libraries(VectorGraphics ${OpenGlLinkers})