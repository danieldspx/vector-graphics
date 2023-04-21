//
// Created by daniel on 18/04/23.
//

#include "RegularShape.h"
#include "../../gl_canvas2d.h"
#include "../../base/enums/MouseState.h"
#include <cmath>

RegularShape::RegularShape(fvec2 center, float radius, int div, float ang): center(center), radius(radius), div(div), ang(ang) {
    resetFocus();
    resetHover();
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

void RegularShape::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    resetHover();

    if (state == MouseState::Up) {
        dragging = rotating = false;
    }

    bool isMouseAction = state == MouseState::Up || state == MouseState::Down;

    if (isIntersecting(position)) {
        hovered = true;
        if (isMouseAction) {
            click(button, state, wheel, direction, position);
        }
    }

    if (isIntersectingRotateButton(position)) {
        if (isMouseAction) {
            clickRotateButton(button, state, wheel, direction, position);
        }
    }

    if (dragging) {
        auto fPos = fvec2{static_cast<float>(position.x), static_cast<float>(position.y)};
        auto centerTranslation = fPos - startDraggingPos;
        center += centerTranslation;
        startDraggingPos = fPos;
    }

    if (rotating) {
        auto fPos = fvec2{static_cast<float>(position.x) - rotateButtonPos.x, static_cast<float>(position.y) - rotateButtonPos.y};
        printf("\nMouse (%f, %f) (%f, %f)\n", fPos.x, fPos.y, startRotatingPos.x, startRotatingPos.y);
//        if (fPos.x == startRotatingPos.x) fPos.x += 0.000001;
        printf("\nangle cos: %f\n", acos( startRotatingPos.scalar(fPos)/(startRotatingPos.modulo() * fPos.modulo()) ));
        angRotateButton = acos( startRotatingPos.scalar(fPos)/(startRotatingPos.modulo() * fPos.modulo()) );
        //ang += angRotateButton;
//        startRotatingPos = fPos;
    }
}

void RegularShape::render(int screenWidth, int screenHeight) {
    CV::colorRGB(r, g, b);
    CV::circleFill(center.x, center.y, radius, div, ang);
    if (hovered) {
        CV::color(1, 0, 0);
        CV::circle(center.x, center.y, radius + 0.2, div, ang);
    }

    if (focused) {
        CV::color(0,0,255);
        CV::rect(hitBoxMin.x, hitBoxMin.y, hitBoxMax.x, hitBoxMax.y);
    }

    renderRotateButton();
}

void RegularShape::renderRotateButton() {
    rotateButtonPos.x = cos(angRotateButton)*(radius + rotateButtonDistance) + center.x;
    rotateButtonPos.y = sin(angRotateButton)*(radius + rotateButtonDistance) + center.y;
    CV::color(0, 1, 0);
    CV::circleFill(rotateButtonPos.x, rotateButtonPos.y, rotateButtonRadius, 50);
}

bool RegularShape::isIntersectingRotateButton(ivec2 position) {
    if (rotateButtonPos.distance(fvec2{static_cast<float>(position.x), static_cast<float>(position.y)}) > radius) {
        return false;
    }
    return true;
}

bool RegularShape::isIntersecting(ivec2 position) {
    float inc = PI_2/div;
    float _ang = ang;
    for(int i = 0; i < div; i++) {
        float x = cos(_ang)*radius + center.x;
        float y = sin(_ang)*radius + center.y;
        if (i == 0) {
            hitBoxMin.x = hitBoxMax.x = center.x;
            hitBoxMin.y = hitBoxMax.y = center.y;
        }
        hitBoxMin.x = hitBoxMin.x > x ? x : hitBoxMin.x;
        hitBoxMin.y = hitBoxMin.y > y ? y : hitBoxMin.y;
        hitBoxMax.x = hitBoxMax.x < x ? x : hitBoxMax.x;
        hitBoxMax.y = hitBoxMax.y < y ? y : hitBoxMax.y;
        _ang += inc;
    }

    if (
        (hitBoxMin.x <= position.x && position.x <= hitBoxMax.x) &&
        (hitBoxMin.y <= position.y && position.y <= hitBoxMax.y)
    ) {
        return true;
    }

    return false;
}

void RegularShape::click(int button, int state, int wheel, int direction, ivec2 position) {
    if (state == MouseState::Down) {
        dragging = focused = true;
        startDraggingPos = fvec2{static_cast<float>(position.x), static_cast<float>(position.y)};
    }
}

void RegularShape::clickRotateButton(int button, int state, int wheel, int direction, ivec2 position) {
    if (state == MouseState::Down) {
        rotating = focused = true;
        startRotatingPos = fvec2{static_cast<float>(position.x), static_cast<float>(position.y)};
    }
}
