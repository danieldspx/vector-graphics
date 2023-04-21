//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "../gl_canvas2d.h"

SceneManager::SceneManager(int screenWidth, int screenHeight) {
    int height = 450;
    screenVectors = new EntityManager();
    auto addEntityCallback = [&](IEntity* entity){
        this->screenVectors->addEntity(entity, 0);
    };
    auto removeFocusedEntity = [&](){
        this->screenVectors->removeFocusedEntity();
    };
    auto changeColor = [&](){
        this->screenVectors->changeFocusedEntityRandomColor();
    };
    auto swapFocusedEntity = [&](int direction){
        this->screenVectors->swapFocusedEntity(direction);
    };

    auto saveOrLoadWorkspace = [&](int action) {
        const char* filename = "figuras.gr";
        if (action > 0) {
            printf("\nSaving entitites to file\n");
            this->screenVectors->saveEntitiesToFile(filename);
        } else {
            printf("\nLoading entities from file\n");
            this->screenVectors->loadEntitiesFromFile(filename);
        }
    };

    toolbox = new Toolbox(ivec2{0, screenHeight/2 - height/2}, 150, height, addEntityCallback, changeColor, removeFocusedEntity, swapFocusedEntity, saveOrLoadWorkspace);
}

void SceneManager::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    toolbox->mouse(button, state, wheel, direction, position);
    // If we are clicking in the toolbox we do not forward the event to the
    // screen vectors because we dont want them to lose the focus
    if (!toolbox->isIntersecting(position)) {
        screenVectors->mouse(button, state, wheel, direction, position);
    }
}

void SceneManager::render(int screenWidth, int screenHeight) {
    CV::clear(0,0,0);
    toolbox->render(screenWidth, screenHeight);
    screenVectors->render(screenWidth, screenHeight);
}
