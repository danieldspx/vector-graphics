//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_ISHAPE_H
#define VECTORGRAPHICS_ISHAPE_H

#include "IEntity.h"
#include <cmath>

class IShape: public IEntity {
public:
    fvec2 startDraggingPos, startRotatingPos, startScalingPos, hitBoxMin, hitBoxMax, rotateButtonPos, scaleShapePos;
    bool dragging, rotating, scaling;
    float angRotateButton, ang, startAng, startAngRotateButton, rotateButtonRadius, rotateButtonDistance, scaleButtonRadius, scaleButtonDistance, startScaleButtonDistance;
    fvec2 center;
    int div;
    float radius, startRadius, minRadius;

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
        dragging = rotating = scaling = false;
        angRotateButton = startAngRotateButton = M_PI_2;
        ang = startAng = 0;
        rotateButtonRadius = 6;
        scaleButtonRadius = 6;
        rotateButtonDistance = 18;
        resetScaleButtonDistance();
    }

    /**
     * Converts the entity to a struct. Here we have a full conversion,
     * meaning the we populate all the fields with useful values
     */
   Entity2File entityToStruc() {
       printf("\nReturning complete struct for entity\n");
       return Entity2File{
               .r = r,
               .g = g,
               .b = b,
               .centerX = center.x,
               .centerY = center.y,
               .radius = radius,
               .div = div,
               .ang = ang
       };
   }
};

#endif //VECTORGRAPHICS_ISHAPE_H
