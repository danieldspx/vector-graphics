//
// Created by daniel on 14/04/23.
//

#include "Toolbox.h"

#include <utility>
#include "Button.h"
#include "../base/vectors/Vector2D.h"
#include "../base/enums/Shape.h"
#include "../gl_canvas2d.h"
#include "ActionButton.h"

Toolbox::Toolbox(ivec2 position, int width, int height, std::function<void(IEntity*)> _addEntityCallback, std::function<void()> _changeColorCallback, std::function<void()> _removeEntityCallback): pos(position), width(width), height(height) {
    addEntityCallback = std::move(_addEntityCallback);
    _addEntityCallback = nullptr;

    changeColorCallback = std::move(_changeColorCallback);
    _changeColorCallback = nullptr;

    removeEntityCallback = std::move(_removeEntityCallback);
    _removeEntityCallback = nullptr;

    entities = new EntityManager();
    int buttonHeight = 50;

    float changeColor[]{66, 245, 138};
    float removeColor[]{245, 66, 96};

    entities->addEntity(new Button(ivec2{pos.x,pos.y}, width, buttonHeight, Triangle, addEntityCallback), 0);
    entities->addEntity(new Button(ivec2{pos.x,pos.y + buttonHeight}, width, buttonHeight, Square, addEntityCallback), 0);
    entities->addEntity(new Button(ivec2{pos.x,pos.y + buttonHeight*2}, width, buttonHeight, Hexagon, addEntityCallback), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*3}, width, buttonHeight, changeColor, "Change Color", changeColorCallback), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*4}, width, buttonHeight, removeColor, "Remove", removeEntityCallback), 0);
}

void Toolbox::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    entities->mouse(button, state, wheel, direction, position);
}

void Toolbox::render(int screenWidth, int screenHeight) {
    pos.y = screenHeight/2 - height/2;
    CV::colorRGB(231, 231, 231);
    CV::rectFill(pos.x, pos.y, pos.x + width, pos.y + height);

    entities->render(screenWidth, screenHeight);
}

bool Toolbox::isIntersecting(ivec2 position) {
    // For now there is no interesting action we want to do when intersecting the toolbox
    return false;
}
