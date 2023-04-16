//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_BUTTON_H
#define VECTORGRAPHICS_BUTTON_H

#include "../base/vectors/Vector2D.h"
#include "../base/interfaces/IEntity.h"

class Button: public IEntity {
public:
    ivec2 pos;
    int width;
    int height;
    const char* label;

    Button(ivec2 pos, int width, int height, const char* label);
    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;
    bool isIntersecting(ivec2 position);
    void click(int button, int state, int wheel, int direction, ivec2 position);
    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_BUTTON_H
