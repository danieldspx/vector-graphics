//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_REGULARSHAPE_H
#define VECTORGRAPHICS_REGULARSHAPE_H


#include "../../base/interfaces/IShape.h"

class RegularShape: public IShape {
public:
    fvec2 translate, center, rectMin, rectMax;
    int div;
    float radius, ang, r, g, b;
    bool hover;


    RegularShape(fvec2 center, float radius, int div);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    void render(int screenWidth, int screenHeight) override;

    bool isIntersecting(ivec2 position);

    void click(int button, int state, int wheel, int direction, ivec2 position);
};


#endif //VECTORGRAPHICS_REGULARSHAPE_H
