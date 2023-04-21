//
// Created by daniel on 21/04/23.
//

#include "ActionButton.h"
#include <string>
#include <iostream>
#include <utility>
#include "../base/vectors/Vector2D.h"
#include "../gl_canvas2d.h"
#include "shapes/RegularShape.h"
#include <stdexcept>

ActionButton::ActionButton(ivec2 pos, int width, int height, float colorRGB[], const char* label, std::function<void()> _actionCallback): pos(pos), width(width), height(height), label(label) {
    actionCallback = std::move(_actionCallback);
    r = colorRGB[0];
    g = colorRGB[1];
    b = colorRGB[2];
    _actionCallback = nullptr;
}

void ActionButton::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    hovered = false;
    if (isIntersecting(position)) {
        hovered = true;
        if (state == 0) {
            click(button, state, wheel, direction, position);
        }
    }
}

bool ActionButton::isIntersecting(ivec2 position) {
    if (
            (pos.x <= position.x && position.x <= pos.x + width) &&
            (pos.y <= position.y && position.y <= pos.y + height)
            ) {
        return true;
    }

    return false;
}

void ActionButton::render(int _screenWidth, int _screenHeight) {
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    CV::colorRGB(r, g, b);
    if (hovered) {
        CV::colorRGB(r*0.8, g*0.8, b*0.8);
    }
    CV::rectFill(pos.x, pos.y, pos.x + width, pos.y + height);
    CV::color(0, 0, 0);
    float stringWidth = (std::string(label).size() * FONT_WIDTH);
    CV::text(pos.x + (width/2 - stringWidth), pos.y + (height/2 - FONT_HEIGHT/2), label);
}

void ActionButton::click(int button, int state, int wheel, int direction, ivec2 position) {
    printf("\nClicou Action: (%d, %d) %d\n", position.x, position.y, button);
    actionCallback();
}