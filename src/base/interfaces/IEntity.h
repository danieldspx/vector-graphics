//
// Created by daniel on 15/04/23.
//

#ifndef VECTORGRAPHICS_IENTITY_H
#define VECTORGRAPHICS_IENTITY_H

#include "IRender.h"
#include "IMouse.h"
#include "IIntersect.h"

class IEntity: public IMouse, public IRender, public IIntersect {};

#endif //VECTORGRAPHICS_IENTITY_H
