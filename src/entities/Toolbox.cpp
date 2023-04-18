//
// Created by daniel on 14/04/23.
//

#include "Toolbox.h"

#include <utility>
#include "Button.h"
#include "../base/vectors/Vector2D.h"
#include "../gl_canvas2d.h"

Toolbox::Toolbox(ivec2 position, int width, int height, std::function<void(IEntity*)> _addEntityCallback): pos(position), width(width), height(height) {
    addEntityCallback = std::move(_addEntityCallback);
    _addEntityCallback = nullptr;
    entities = new EntityManager();
    entities->addEntity(new Button(ivec2{pos.x,pos.y}, 100, 50, "Circle", addEntityCallback), 0);
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
