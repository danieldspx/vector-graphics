//
// Created by daniel on 18/04/23.
//

#ifndef VECTORGRAPHICS_ISHAPE_H
#define VECTORGRAPHICS_ISHAPE_H

#include "IEntity.h"

class IShape: public IEntity {
public:
    fvec2 translate, startDraggingPos, hitBoxMin, hitBoxMax;
    bool dragging;

    IShape() {
        translate = fvec2 {0,0};
        dragging = false;
    }
};

#endif //VECTORGRAPHICS_ISHAPE_H
