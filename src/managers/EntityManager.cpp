//
// Created by daniel on 14/04/23.
//

#include "EntityManager.h"
#include "../base/vectors/Vector2D.h"
#include <iostream>

EntityManager::EntityManager() {
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
    for (const auto& pair: entities) {
        for (auto entity: pair.second) {
            entity->mouse(button, state, wheel, direction, position);
        }
    }
}
