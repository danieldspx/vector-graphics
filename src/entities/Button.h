//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_MOUSEBUTTON_H
#define VECTORGRAPHICS_BUTTON_H

#include "../base/vectors/Vector2D.h"
#include "../base/interfaces/IEntity.h"
#include "../base/enums/Shape.h"
#include <functional>

class Button: public IEntity {
public:
    ivec2 pos;
    int width, height, screenWidth, screenHeight;
    const char* label;
    Shape shapeType;
    std::function<void(IEntity*)> addEntityCallback;

    Button(ivec2 pos, int width, int height, Shape shapeType, std::function<void(IEntity*)> addEntityCallback);

    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;

    bool isIntersecting(ivec2 position);

    void click(int button, int state, int wheel, int direction, ivec2 position);

    void render(int screenWidth, int screenHeight) override;

    void createShape();

    void createTriangle();

    void createSquare();

    void createHexagon();
};


#endif //VECTORGRAPHICS_MOUSEBUTTON_H
