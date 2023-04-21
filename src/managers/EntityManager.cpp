//
// Created by daniel on 14/04/23.
//

#include "EntityManager.h"
#include "../base/enums/MouseButton.h"
#include "../base/enums/MouseState.h"
#include <iostream>
#include <algorithm>

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

void EntityManager::changeFocusedEntityRandomColor() {
    if (entityController.focused) {
        entityController.focused->changeToRandomColor();
    }
}

void EntityManager::mouse(int button, int state, int wheel, int direction, ivec2 position) {
    entityController.hovered = nullptr;

    // We need to reset the focused entity every time because we might be clicking another shape that overlaps
    // an already focused entity. Even if we are clicking in the focused shape we can safely do this because
    // the code below will focus it again.
    if (button == MouseButton::Left && state == MouseState::Down && entityController.focused) {
        entityController.focused->resetFocus();
        entityController.focused->resetHover();
        entityController.focused = nullptr;
    }

    // We iterate in reverse because the ones in the latest positions are the ones in the top
    // So any interaction happens with them first
    for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
        const auto& pair = *it;
        for (auto vecIt = pair.second.rbegin(); vecIt != pair.second.rend(); ++vecIt) {
            auto entity = (*vecIt);
            entity->mouse(button, state, wheel, direction, position);
            auto shapeEntity = dynamic_cast<IShape *>(entity);
            if (entity->isIntersecting(position)) {
                if (entity->isFocused() && !entityController.focused) {
                    entityController.focused = entity;
                }

                if (entity->isHovered() && !entityController.hovered) {
                    entityController.hovered = entity;
                }

                if (shapeEntity && shapeEntity->isDragging() && !entityController.shapeDragging) {
                    entityController.shapeDragging = shapeEntity;
                }
            }

            // Disble focus if it is not the shape being focused
            if (entityController.focused && entity != entityController.focused) {
                entity->resetFocus();
            }
            // Disble hover if there is some shape being dragged OR it is not the shape being hovered
            if (entityController.shapeDragging || (entityController.hovered && entity != entityController.hovered)) {
                entity->resetHover();
            }

            if (shapeEntity && entityController.shapeDragging && shapeEntity != entityController.shapeDragging) {
                shapeEntity->resetDrag();
            }
        }
    }

    if (button == MouseButton::Left && state == MouseState::Up) {
        if (entityController.shapeDragging) {
            entityController.shapeDragging->resetDrag();
            entityController.shapeDragging = nullptr;
        }
    }
}

void EntityManager::removeFocusedEntity() {
    printf("\nRemoving focused entity\n");
    if (entityController.focused) {
        for (auto& pair: entities) {
            auto& v = pair.second;
            v.erase(std::remove(v.begin(), v.end(), entityController.focused), v.end());
        }
    }
}

void EntityManager::swapFocusedEntity(int direction) {
    printf("\nSwapping focused entity with %s entity\n", direction > 0 ? "next" : "previous");
    if (entityController.focused) {
        for (auto& pair : entities) {
            auto& v = pair.second;
            auto it = std::find(v.begin(), v.end(), entityController.focused);
            if (it != v.end() && ((direction > 0 && std::next(it) != v.end()) || (direction < 0 && it != v.begin()))) {
                auto newIt = std::next(it, direction);
                std::iter_swap(it, newIt);
                entityController.focused = *newIt;
                break;
            }
        }
    }
}

