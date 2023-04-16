//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_TOOLBOX_H
#define VECTORGRAPHICS_TOOLBOX_H


#include "../base/interfaces/IRender.h"
#include "../base/interfaces/IEntity.h"
#include "../managers/EntityManager.h"

class Toolbox: public IEntity {
public:
    ivec2 pos;
    EntityManager* entities;
    int width;
    int height;

    Toolbox(ivec2 position, int width, int height);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_TOOLBOX_H
