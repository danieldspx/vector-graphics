//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_ISHAPE_H
#define VECTORGRAPHICS_ISHAPE_H

#include "IEntity.h"
#include <cmath>

class IShape: public IEntity {
public:
    fvec2 translate, startDraggingPos, startRotatingPos, startScalingPos, hitBoxMin, hitBoxMax, rotateButtonPos, scaleShapePos;
    bool dragging, rotating, scaling;
    float angRotateButton, ang, startAng, startAngRotateButton, rotateButtonRadius, rotateButtonDistance, scaleButtonRadius, scaleButtonDistance, startScaleButtonDistance;

    bool isDragging() const {
        return dragging;
    }

    void resetDrag() {
        dragging = false;
    }

    void resetScaleButtonDistance() {
        scaleButtonDistance = 2;
    }

    IShape() {
        translate = fvec2 {0,0};
        dragging = rotating = scaling = false;
        angRotateButton = startAngRotateButton = M_PI_2;
        ang = startAng = 0;
        rotateButtonRadius = 6;
        scaleButtonRadius = 6;
        rotateButtonDistance = 18;
        resetScaleButtonDistance();
    }


};

#endif //VECTORGRAPHICS_ISHAPE_H
