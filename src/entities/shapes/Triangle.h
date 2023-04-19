//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_TRIANGLE_H
#define VECTORGRAPHICS_TRIANGLE_H


#include "../../base/interfaces/IEntity.h"
#include "../../base/vectors/Vector2D.h"

class Triangle: public IEntity {
public:
    int screenWidth, screenHeight;
    fvec2 translate;
    fvec2 p1, p2, p3;

    Triangle(fvec2 p1, fvec2 p2, fvec2 p3, fvec2 translate);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    void render(int screenWidth, int screenHeight) override;
};


#endif //VECTORGRAPHICS_TRIANGLE_H
