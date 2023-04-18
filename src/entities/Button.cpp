//
// Created by daniel on 14/04/23.
//

#include <string>
#include <iostream>
#include "Button.h"
#include "../base/vectors/Vector2D.h"
#include "../gl_canvas2d.h"

Button::Button(ivec2 pos, int width, int height, const char* label): pos(pos), width(width), height(height), label(label) {
    hovered = false;
}

void Button::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    hovered = false;
    if (isIntersecting(position)) {
        hovered = true;
        if (state == 0) {
            click(button, state, wheel, direction, position);
        }
    }
}

bool Button::isIntersecting(ivec2 position) {
    if (
        (pos.x <= position.x && position.x <= pos.x + width) &&
        (pos.y <= position.y && position.y <= pos.y + height)
    ) {
        return true;
    }

    return false;
}

void Button::render(int screenWidth, int screenHeight) {
    CV::colorRGB(168, 255, 249);
    if (hovered) {
        CV::colorRGB(151, 232, 226);
    }
    CV::rectFill(pos.x, pos.y, pos.x + width, pos.y + height);
    CV::color(0, 0, 0);
    float stringWidth = (std::string(label).size() * FONT_WIDTH);
    CV::text(pos.x + (width/2 - stringWidth), pos.y + (height/2 - FONT_HEIGHT/2), label);
}

void Button::click(int button, int state, int wheel, int direction, ivec2 position) {
    printf("\nClicou: (%d, %d) %d\n", position.x, position.y, button);
}