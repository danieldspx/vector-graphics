//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "../gl_canvas2d.h"

SceneManager::SceneManager(int screenWidth, int screenHeight) {
    int height = 500;
    toolbox = new Toolbox(ivec2{0, screenHeight/2 - height/2}, 100, height);
}

void SceneManager::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    toolbox->mouse(button, state, wheel, direction, position);
}

void SceneManager::render(int screenWidth, int screenHeight) {
    CV::clear(0,0,0);
    toolbox->render(screenWidth, screenHeight);
}
