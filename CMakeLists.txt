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
        src/Vector2.h
        src/gl_canvas2d.cpp src/gl_canvas2d.h src/base/interfaces/IRender.h src/base/vectors/Vector2D.h src/base/interfaces/IMouse.h src/managers/SceneManager.cpp src/managers/SceneManager.h src/entities/Button.cpp src/entities/Button.h src/entities/Toolbox.cpp src/entities/Toolbox.h src/managers/EntityManager.cpp src/managers/EntityManager.h src/base/interfaces/IEntity.h src/base/enums/Shape.h src/base/interfaces/IShape.h src/entities/shapes/RegularShape.cpp src/entities/shapes/RegularShape.h src/base/enums/MouseButton.h src/base/enums/MouseState.h src/base/interfaces/IIntersect.h src/entities/ActionButton.cpp src/entities/ActionButton.h)

target_link_libraries(VectorGraphics ${OpenGlLinkers})