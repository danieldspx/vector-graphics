//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "../gl_canvas2d.h"

SceneManager::SceneManager(int screenWidth, int screenHeight) {
    int height = 500;
    screenVectors = new EntityManager();
    auto addEntityCallback = [&](IEntity* entity){
        this->screenVectors->addEntity(entity, 0);
    };
    toolbox = new Toolbox(ivec2{0, screenHeight/2 - height/2}, 100, height, addEntityCallback);
}

void SceneManager::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    toolbox->mouse(button, state, wheel, direction, position);
    screenVectors->mouse(button, state, wheel, direction, position);
}

void SceneManager::render(int screenWidth, int screenHeight) {
    CV::clear(0,0,0);
    toolbox->render(screenWidth, screenHeight);
    screenVectors->render(screenWidth, screenHeight);
}
