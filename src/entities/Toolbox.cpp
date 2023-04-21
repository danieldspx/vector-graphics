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

Toolbox::Toolbox(ivec2 position, int width, int height, std::function<void(IEntity*)> _addEntityCallback, std::function<void()> _changeColorCallback, std::function<void()> _removeEntityCallback, std::function<void(int)> _swapFocusedEntity, std::function<void(int)> _saveOrLoadWorkspace): pos(position), width(width), height(height) {
    addEntityCallback = std::move(_addEntityCallback);
    _addEntityCallback = nullptr;

    changeColorCallback = std::move(_changeColorCallback);
    _changeColorCallback = nullptr;

    removeEntityCallback = std::move(_removeEntityCallback);
    _removeEntityCallback = nullptr;

    swapFocusedEntity = std::move(_swapFocusedEntity);
    _swapFocusedEntity = nullptr;

    saveOrLoadWorkspace = std::move(_saveOrLoadWorkspace);
    _saveOrLoadWorkspace = nullptr;

    entities = new EntityManager();
    int buttonHeight = 50;

    float changeColor[]{66, 245, 138};
    float removeColor[]{245, 66, 96};
    float sendBackColor[]{238, 255, 48};
    float sendForwardColor[]{48, 255, 179};
    float saveColor[]{138, 102, 255};
    float loadColor[]{255, 158, 102};

    auto sendForward = [&](){
        this->swapFocusedEntity(1);
    };
    auto sendBackward = [&](){
        this->swapFocusedEntity(-1);
    };
    auto saveWorkspace = [&](){
        this->saveOrLoadWorkspace(1);
    };
    auto loadWorkspace = [&](){
        this->saveOrLoadWorkspace(-1);
    };
    entities->addEntity(new Button(ivec2{pos.x,pos.y}, width, buttonHeight, Triangle, addEntityCallback), 0);
    entities->addEntity(new Button(ivec2{pos.x,pos.y + buttonHeight}, width, buttonHeight, Square, addEntityCallback), 0);
    entities->addEntity(new Button(ivec2{pos.x,pos.y + buttonHeight*2}, width, buttonHeight, Hexagon, addEntityCallback), 0);

    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*3}, width, buttonHeight, changeColor, "Change Color", changeColorCallback), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*4}, width, buttonHeight, removeColor, "Remove", removeEntityCallback), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*5}, width, buttonHeight, sendForwardColor, "Send Forward", sendForward), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*6}, width, buttonHeight, sendBackColor, "Send Backward", sendBackward), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*7}, width, buttonHeight, saveColor, "Save", saveWorkspace), 0);
    entities->addEntity(new ActionButton(ivec2{pos.x,pos.y + buttonHeight*8}, width, buttonHeight, loadColor, "Load", loadWorkspace), 0);
}

void Toolbox::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    entities->mouse(button, state, wheel, direction, position);
}

void Toolbox::render(int screenWidth, int screenHeight) {
    CV::color(1, 0, 0);
    CV::rectFill(pos.x, pos.y, pos.x + width, pos.y + height);

    entities->render(screenWidth, screenHeight);
}

bool Toolbox::isIntersecting(ivec2 position) {
    if (
            (pos.x <= position.x && position.x <= pos.x + width) &&
            (pos.y <= position.y && position.y <= pos.y + height)
            ) {
        return true;
    }

    return false;
}
