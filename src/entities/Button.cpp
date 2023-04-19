//
// Created by daniel on 14/04/23.
//

#include <string>
#include <iostream>
#include <utility>
#include "Button.h"
#include "../base/vectors/Vector2D.h"
#include "../gl_canvas2d.h"
#include "shapes/Triangle.h"
#include "shapes/RegularShape.h"
#include <stdexcept>

Button::Button(ivec2 pos, int width, int height, Shape shapeType, std::function<void(IEntity*)> _addEntityCallback): pos(pos), width(width), height(height), shapeType(shapeType) {
    addEntityCallback = std::move(_addEntityCallback);
    _addEntityCallback = nullptr;
    hovered = false;

    switch (shapeType) {
        case Triangle:
            label = "Triangle";
            break;
        case Square:
            label = "Square";
            break;
        case Hexagon:
            label = "Hexagon";
            break;
        default:
            throw std::invalid_argument("The provided Shade Type is not yet implemented");
    }
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

void Button::render(int _screenWidth, int _screenHeight) {
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
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
    createShape();
}

void Button::createShape() {
    switch (shapeType) {
        case Triangle:
            createTriangle();
            break;
        case Square:
            createSquare();
            break;
        case Hexagon:
            createHexagon();
            break;
        default:
            throw std::invalid_argument("There is no factory method for the provided shape yet.");
    }
}

void Button::createTriangle() {
    printf("\nAdding Triangle Entity");
    float radius = 30;
    addEntityCallback(new RegularShape(fvec2{static_cast<float>(screenWidth/2), static_cast<float>(screenHeight/2)}, radius, 3));
}

void Button::createSquare() {
    printf("\nAdding Square Entity");
    float radius = 30;
    addEntityCallback(new RegularShape(fvec2{static_cast<float>(screenWidth/2), static_cast<float>(screenHeight/2)}, radius, 4));
}

void Button::createHexagon() {
    printf("\nAdding Hexagon Entity");
    float radius = 30;
    addEntityCallback(new RegularShape(fvec2{static_cast<float>(screenWidth/2), static_cast<float>(screenHeight/2)}, radius, 5));
}