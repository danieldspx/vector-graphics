//
// Created by daniel on 18/04/23.
//

#include "RegularShape.h"
#include "../../gl_canvas2d.h"

RegularShape::RegularShape(fvec2 center, float radius, int div): center(center), radius(radius), div(div) {
    ang = 0;
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

void RegularShape::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    hover = false;
    if (isIntersecting(position)) {
        hover = true;
        if (state == 0) {
            click(button, state, wheel, direction, position);
        }
    }
}

void RegularShape::render(int screenWidth, int screenHeight) {
    CV::colorRGB(r, g, b);
    CV::circleFill(center.x, center.y, radius, div, ang);
    if (hover) {
        CV::color(1, 0, 0);
        CV::circle(center.x, center.y, radius + 0.2, div, ang);
    }

}

bool RegularShape::isIntersecting(ivec2 position) {
    bool intersecting = true;
    float inc = PI_2/div;
    float _ang = 0;
    fvec2 min, max;
    for(int i = 0; i < div; i++) {
        float x = cos(_ang)*radius + center.x;
        float y = sin(_ang)*radius + center.y;
        if (i == 0) {
            min.x = max.x = x;
            min.y = max.y = x;
        }
        min.x = min.x > x ? x : min.x;
        min.y = min.y > y ? y : min.y;
        max.x = max.x < x ? x : max.x;
        max.y = max.y < y ? y : max.y;
        _ang += inc;
    }

    if (
        (min.x <= position.x && position.x <= max.x) &&
        (min.y <= position.y && position.y <= max.y)
    ) {
        return true;
    }

    return false;
}

void RegularShape::click(int button, int state, int wheel, int direction, ivec2 position) {
    printf("\nCliclouuu");
}


