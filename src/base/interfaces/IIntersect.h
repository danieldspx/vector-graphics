//
// Created by daniel on 19/04/23.
//

#ifndef VECTORGRAPHICS_IINTERSECT_H
#define VECTORGRAPHICS_IINTERSECT_H

#include "../vectors/Vector2D.h"

class IIntersect {
public:
    virtual bool isIntersecting(ivec2 position) = 0;
};

#endif //VECTORGRAPHICS_IINTERSECT_H
