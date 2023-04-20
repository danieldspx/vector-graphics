//
// Created by daniel on 14/04/23.
//

#include "EntityManager.h"
#include "../base/vectors/Vector2D.h"
#include "../base/enums/MouseButton.h"
#include "../base/enums/MouseState.h"
#include <iostream>

EntityManager::EntityManager() {
    entityController = EntityController{nullptr, nullptr};
}

void EntityManager::addEntity(IEntity *entity, uint layer = 0) {
//    std::cout << "[ENTITY] Pushing entity back to the layer: " << layer << std::endl;
    auto it = this->entities.find(layer);
    if (it == this->entities.end()) {
        this->entities.insert(std::pair<uint, std::vector<IEntity *>>(layer, std::vector<IEntity *>{entity}));
    } else {
        // Adds the entity to the Vector
        it->second.push_back(entity);
    }
}

void EntityManager::render(int screenWidth, int screenHeight) {
    for (auto pair: entities) {
        for (auto entitty: pair.second) {
            entitty->render(screenWidth, screenHeight);
        }
    }
}

void EntityManager::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
        const auto& pair = *it;
        for (auto vecIt = pair.second.rbegin(); vecIt != pair.second.rend(); ++vecIt) {
            auto entity = (*vecIt);
            entity->mouse(button, state, wheel, direction, position);
            if (entity->isIntersecting(position)) {
                if (entity->isFocused()) {
                    entityController.focused = entity;
                    entityController.hovered = nullptr;
                } else if (entity->isHovered()) {
                    entityController.focused = nullptr;
                    entityController.hovered = entity;
                }
            }

            // Disble focus if it is not the shape being focused
            if (entityController.focused && entity != entityController.focused) {
                entity->resetFocus();
            }
            // Disble hover if it is not the shape being hovered
            if (entityController.hovered && entity != entityController.hovered) {
                entity->resetHover();
            }
        }
    }

    if (button == MouseButton::Left && state == MouseState::Up) {
        // We iterate in reverse because the ones in the latest positions are the ones in the top
        // So any interaction happens with them first
        if (entityController.focused && !entityController.focused->isIntersecting(position)) {
            entityController.focused->resetFocus();
            entityController.focused->resetHover();
            entityController.focused = nullptr;
            entityController.hovered = nullptr;
        }
    }
}
