//
// Created by daniel on 15/04/23.
//

#ifndef VECTORGRAPHICS_IENTITY_H
#define VECTORGRAPHICS_IENTITY_H

#include "IRender.h"
#include "IMouse.h"
#include "IIntersect.h"

class IEntity: public IMouse, public IRender, public IIntersect {
public:
    float r, g, b;
    void changeToRandomColor() {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    };
    void setToColor(float _r, float _g, float _b) {
        r = _r;
        g = _g;
        b = _b;
    };
    /**
     * Struct create with the only purpose to save the entity into a binary file
     */
   struct Entity2File {
       float r;
       float g;
       float b;
       float centerX;
       float centerY;
       float radius;
       int div;
       float ang;
   };
   /**
    * Converts an entity to a basic struct
    */
   Entity2File entityToStruc() {
       printf("EntityToFile Will return basic struct");
       return Entity2File{r, g, b};
   };
};

#endif //VECTORGRAPHICS_IENTITY_H
