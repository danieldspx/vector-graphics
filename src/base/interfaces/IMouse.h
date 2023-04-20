//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_IMOUSE_H
#define VECTORGRAPHICS_IMOUSE_H

#include "../vectors/Vector2D.h"

class IMouse {
public:
    virtual void mouse(int button, int state, int wheel, int direction, ivec2 position) = 0;
    bool hovered, focused;

    bool isFocused() const {
        return focused;
    }

    bool isHovered() const {
        return hovered;
    }

    void resetFocus() {
        focused = false;
    }

    void resetHover() {
        hovered = false;
    }

    IMouse() {
        hovered = focused = false;
    }
};

#endif //VECTORGRAPHICS_IMOUSE_H
