//
// Created by daniel on 18/04/23.
//

#include "RegularShape.h"
#include "../../gl_canvas2d.h"
#include "../../base/enums/MouseState.h"
#include <cmath>

RegularShape::RegularShape(fvec2 _center, float _radius, int _div, float _ang) {
    resetFocus();
    resetHover();
    center = _center;
    radius = _radius;
    div = _div;
    startRadius = _radius;
    ang = startAng = _ang;
    minRadius = 15;
    changeToRandomColor();
}

void RegularShape::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    resetHover();

    if (state == MouseState::Up) {
        dragging = rotating = scaling = false;
    }

    bool isMouseAction = state == MouseState::Up || state == MouseState::Down;

    if (isIntersectingRotateButton(position)) {
        if (isMouseAction) {
            clickRotateButton(button, state, wheel, direction, position);
        }
    }

    if (isIntersectingScaleButton(position)) {
        if (isMouseAction) {
            clickScaleButton(button, state, wheel, direction, position);
        }
    }

    if (isIntersecting(position) && !isIntersectingRotateButton(position)) {
        hovered = true;
        if (isMouseAction) {
            click(button, state, wheel, direction, position);
        }
    }

    if (dragging) {
        auto fPos = fvec2{static_cast<float>(position.x), static_cast<float>(position.y)};
        auto centerTranslation = fPos - startDraggingPos;
        center += centerTranslation;
        startDraggingPos = fPos;
    }

    if (rotating) {
        auto fPos = fvec2{static_cast<float>(position.x) - center.x, static_cast<float>(position.y) - center.y}.unit();
        auto rotationAngle = startRotatingPos.angle(fPos);
        angRotateButton = startAngRotateButton + rotationAngle;
        ang = startAng + rotationAngle;
    }

    if (scaling) {
        auto fPos = fvec2{static_cast<float>(position.x), static_cast<float>(position.y)};
        radius = startRadius + (startScalingPos.y - fPos.y);
        if (radius >= minRadius) {
            scaleButtonDistance = startScaleButtonDistance + (startScalingPos.y - fPos.y);
        } else {
            radius = minRadius;
        }
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
    renderScaleShapeButton();
}



void RegularShape::renderRotateButton() {
    rotateButtonPos.x = cos(angRotateButton)*(radius + rotateButtonDistance) + center.x;
    rotateButtonPos.y = sin(angRotateButton)*(radius + rotateButtonDistance) + center.y;
    CV::color(0, 1, 0);
    CV::circleFill(rotateButtonPos.x, rotateButtonPos.y, rotateButtonRadius, 50);
}

void RegularShape::renderScaleShapeButton() {
    scaleShapePos.x = cos(-M_PI_2)*(startRadius + scaleButtonDistance) + center.x;
    scaleShapePos.y = sin(-M_PI_2)*(startRadius + scaleButtonDistance) + center.y;
    CV::color(1, 0, 0);
    CV::circleFill(scaleShapePos.x, scaleShapePos.y, scaleButtonRadius, 4, PI/4);
}

bool RegularShape::isIntersectingRotateButton(ivec2 position) {
    if (rotateButtonPos.distance(fvec2{static_cast<float>(position.x), static_cast<float>(position.y)}) > rotateButtonRadius) {
        return false;
    }
    return true;
}

bool RegularShape::isIntersectingScaleButton(ivec2 position) {
    /**
     * Since we draw the this button using the same method for drawing any regular shape
     * we need to figure what the coordinates of each point is before checking if the point
     * is intercepting the button
     */
    float inc = PI_2/4;
    float _ang = -M_PI_2;
    fvec2 scaleHitBoxMin, scaleHitBoxMax;
    for(int i = 0; i < 4; i++) {
        float x = cos(_ang)*scaleButtonRadius + scaleShapePos.x;
        float y = sin(_ang)*scaleButtonRadius + scaleShapePos.y;
        if (i == 0) {
            scaleHitBoxMin.x = scaleHitBoxMax.x = x;
            scaleHitBoxMin.y = scaleHitBoxMax.y = y;
        }
        scaleHitBoxMin.x = scaleHitBoxMin.x > x ? x : scaleHitBoxMin.x;
        scaleHitBoxMin.y = scaleHitBoxMin.y > y ? y : scaleHitBoxMin.y;
        scaleHitBoxMax.x = scaleHitBoxMax.x < x ? x : scaleHitBoxMax.x;
        scaleHitBoxMax.y = scaleHitBoxMax.y < y ? y : scaleHitBoxMax.y;
        _ang += inc;
    }

    if (
            (scaleHitBoxMin.x <= position.x && position.x <= scaleHitBoxMax.x) &&
            (scaleHitBoxMin.y <= position.y && position.y <= scaleHitBoxMax.y)
            ) {
        return true;
    }

    return false;
}

bool RegularShape::isIntersecting(ivec2 position) {
    /**
     * Since we draw the this button using the same method for drawing any regular shape
     * we need to figure what the coordinates of each point is before checking if the point
     * is intercepting the button
     */
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
        startAngRotateButton = angRotateButton;
        startAng = ang;
        startRotatingPos = fvec2{static_cast<float>(position.x) - center.x, static_cast<float>(position.y) - center.y}.unit();
    }
}

void RegularShape::clickScaleButton(int button, int state, int wheel, int direction, ivec2 position) {
    if (state == MouseState::Down) {
        scaling = focused = true;
        startScalingPos = fvec2{static_cast<float>(position.x), static_cast<float>(position.y)};
        resetScaleButtonDistance();
        startScaleButtonDistance = scaleButtonDistance;
        startRadius = radius;
    }
}
