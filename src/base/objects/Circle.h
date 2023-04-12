//
// Created by daniel on 12/04/23.
//

#ifndef VECTORGRAPHICS_CIRCLE_H
#define VECTORGRAPHICS_CIRCLE_H

#include "../interfaces/IRender.h"

class Circle: public IRender {
    void render() override;
};


#endif //VECTORGRAPHICS_CIRCLE_H
