//
// Created by daniel on 21/04/23.
//

#ifndef VECTORGRAPHICS_ACTIONBUTTON_H
#define VECTORGRAPHICS_ACTIONBUTTON_H

#include <string>
#include <iostream>
#include <utility>
#include "../base/vectors/Vector2D.h"
#include "../gl_canvas2d.h"
#include "shapes/RegularShape.h"
#include "../base/interfaces/IEntity.h"
#include <stdexcept>
#include <functional>

/**
 * Class that is meant to hold Buttons that only perform an action.
 * They do so by calling the provided callback.
 */
class ActionButton: public IEntity {
public:
    ivec2 pos;
    int width, height, screenWidth, screenHeight;
    const char* label;
    std::function<void()> actionCallback;

    ActionButton(ivec2 pos, int width, int height, float colorRGB[], const char* label, std::function<void()> actionCallback);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    bool isIntersecting(ivec2 position) override;

    void click(int button, int state, int wheel, int direction, ivec2 position);

    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_ACTIONBUTTON_H
