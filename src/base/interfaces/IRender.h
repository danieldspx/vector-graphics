//
// Created by daniel on 12/04/23.
//

#ifndef VECTORGRAPHICS_IRENDER_H
#define VECTORGRAPHICS_IRENDER_H

class IRender {
public:
    virtual void render(int screenWidth, int screenHeight) = 0;
};

#endif
