//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_TOOLBOX_H
#define VECTORGRAPHICS_TOOLBOX_H


#include <functional>
#include "../base/interfaces/IRender.h"
#include "../base/interfaces/IEntity.h"
#include "../managers/EntityManager.h"

class Toolbox: public IEntity {
public:
    ivec2 pos;
    EntityManager* entities;
    int width;
    int height;
    std::function<void(IEntity*)> addEntityCallback;
    std::function<void()> changeColorCallback;
    std::function<void()> removeEntityCallback;

    bool isIntersecting(ivec2 position) override;

    Toolbox(ivec2 position, int width, int height, std::function<void(IEntity*)> addEntityCallback, std::function<void()> changeColorCallback, std::function<void()> _removeEntityCallback);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_TOOLBOX_H
