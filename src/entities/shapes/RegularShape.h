//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_REGULARSHAPE_H
#define VECTORGRAPHICS_REGULARSHAPE_H


#include "../../base/interfaces/IShape.h"

class RegularShape: public IShape {
public:
    float startRadius, minRadius;

    RegularShape(fvec2 center, float radius, int div, float ang);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    void render(int screenWidth, int screenHeight) override;

    bool isIntersecting(ivec2 position) override;

    void click(int button, int state, int wheel, int direction, ivec2 position);

    void renderRotateButton();

    bool isIntersectingRotateButton(ivec2 position);

    void clickRotateButton(int button, int state, int wheel, int direction, ivec2 position);

    void renderScaleShapeButton();

    void clickScaleButton(int button, int state, int wheel, int direction, ivec2 position);

    bool isIntersectingScaleButton(ivec2 position);
};


#endif //VECTORGRAPHICS_REGULARSHAPE_H
