//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_SCENEMANAGER_H
#define VECTORGRAPHICS_SCENEMANAGER_H


#include "../base/interfaces/IMouse.h"
#include "../base/interfaces/IRender.h"
#include "../entities/Toolbox.h"

class SceneManager: public IMouse, public IRender {
public:
    Toolbox* toolbox;
    EntityManager* screenVectors;

    SceneManager(int screenWidth, int screenHeight);
    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;
    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_SCENEMANAGER_H
