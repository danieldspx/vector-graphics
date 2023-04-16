//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_IMOUSE_H
#define VECTORGRAPHICS_IMOUSE_H

#include "../vectors/Vector2D.h"

class IMouse {
public:
    virtual void mouse(int button, int state, int wheel, int direction, ivec2 position) = 0;
};

#endif //VECTORGRAPHICS_IMOUSE_H
