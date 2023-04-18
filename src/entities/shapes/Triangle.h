//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_TRIANGLE_H
#define VECTORGRAPHICS_TRIANGLE_H


#include "../../base/interfaces/IEntity.h"
#include "../../base/vectors/Vector2D.h"

class Triangle: public IEntity {
public:
    ivec2 center, p1, p2, p3;
    float r, g, b, size;

    Triangle(ivec2 center, float size, float r, float g, float b);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_TRIANGLE_H
