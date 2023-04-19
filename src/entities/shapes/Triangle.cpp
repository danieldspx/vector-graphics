//
// Created by daniel on 18/04/23.
//

#include "Triangle.h"
#include "../../gl_canvas2d.h"

void Triangle::mouse(int button, int state, int wheel, int direction, ivec2 position) {

}

void Triangle::render(int _screenWidth, int _screenHeight) {
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    glPushMatrix(); // pushes the current matrix stack down by one, duplicating the current matrix. That is, after a glPushMatrix call, the matrix on top of the stack is identical to the one below it.
    CV::translate(translate.x, translate.y);
    CV::colorRGB(84, 147, 255);
    float vx[] = { p1.x, p2.x, p3.x };
    float vy[] = { p1.y, p2.y, p3.y };
    CV::polygonFill(vx, vy, 3);
    glPopMatrix(); // pops the current matrix stack, replacing the current matrix with the one below it on the stack.
}

Triangle::Triangle(fvec2 p1, fvec2 p2, fvec2 p3, fvec2  translate): p1(p1), p2(p2), p3(p3), translate(translate) {
    // We set to 1 just as an initialization value and also avoid any division by zero
    screenHeight = 1;
    screenWidth = 1;
}
