//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_ISHAPE_H
#define VECTORGRAPHICS_ISHAPE_H

#include "IEntity.h"
#include <cmath>

class IShape: public IEntity {
public:
    fvec2 translate, startDraggingPos, startRotatingPos, hitBoxMin, hitBoxMax, rotateButtonPos;
    bool dragging, rotating;
    float angRotateButton, ang, startAng, startAngRotateButton, rotateButtonRadius, rotateButtonDistance;

    bool isDragging() const {
        return dragging;
    }

    void resetDrag() {
        dragging = false;
    }

    IShape() {
        translate = fvec2 {0,0};
        dragging = rotating = false;
        angRotateButton = startAngRotateButton = M_PI_2;
        ang = startAng = 0;
        rotateButtonRadius = 6;
        rotateButtonDistance = 18;
    }
};

#endif //VECTORGRAPHICS_ISHAPE_H
