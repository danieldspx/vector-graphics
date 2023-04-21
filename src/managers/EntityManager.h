//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_ENTITYMANAGER_H
#define VECTORGRAPHICS_ENTITYMANAGER_H

#include <map>
#include <vector>
#include "../base/interfaces/IRender.h"
#include "../base/interfaces/IMouse.h"
#include "../base/interfaces/IEntity.h"
#include "../base/interfaces/IShape.h"

#define uint unsigned int

/**
 * Manages the entities by doing the following:
 * - Manages entities between layers allowing them to move between them;
 * - Forwards mouse events to entities that implements the IMouse interface;
 * - Renders entities that implements the IRender interface.
 */
class EntityManager: public IRender, public IMouse {
public:
    struct EntityController {
        IEntity* focused;
        IEntity* hovered;
        IShape* shapeDragging;
    };
    std::map<uint, std::vector<IEntity*>> entities;

    EntityManager();

    void addEntity(IEntity* entity, uint layer);

    void render(int screenWidth, int screenHeight) override;
    void mouse(int button, int state, int wheel, int direction, ivec2 position) override;
    void changeFocusedEntityRandomColor();
    void removeFocusedEntity();
    void swapFocusedEntity(int direction);
private:
    EntityController entityController{};
};


#endif //VECTORGRAPHICS_ENTITYMANAGER_H
