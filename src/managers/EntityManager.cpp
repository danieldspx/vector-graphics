//
// Created by daniel on 14/04/23.
//

#include "EntityManager.h"
#include "../base/enums/MouseButton.h"
#include "../base/enums/MouseState.h"
#include "../entities/shapes/RegularShape.h"
#include <iostream>
#include <algorithm>
#include <fstream>

EntityManager::EntityManager() {
    entityController = EntityController{nullptr, nullptr};
}

void EntityManager::addEntity(IEntity *entity, uint layer = 0) {
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
            // We need this conversion to make sure we have a IShape ref
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

            // If the entity is a shape and there is a shape currently being dragged and the current entity is not
            // the shape being dragged, reset the drag state
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

/**
 * This method aims to swap entities in the vector. This is usefull if you
 * want to draw some entities on top of each other. The reason is because
 * the render iterates through those entities in order, so the ones that
 * are drawn first will be below the ones drawn later.
 *
 * @param direction Direction of swap. If 1 is provided it swaps with the next entity. If -1 is provided
 * it swaps with the previous entity.
 */
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

/**
 * Saves entities to the provided file
 * @param filePath
 */
void EntityManager::saveEntitiesToFile(const std::string& filePath) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }

    std::vector<IEntity*> entitiesVect = entities[0];
    printf("\nSaving entities...\n");
    auto* sts = new IEntity::Entity2File[entitiesVect.size()];
    printf("\nTotal entities: %zu\n", entitiesVect.size());

    int pos = 0;
    for (auto& entity: entitiesVect) {
        sts[pos] = dynamic_cast<IShape *>(entity)->entityToStruc();
        printf("\nEntity to struct at: (%f, %f)\n", sts[pos].centerX, sts[pos].centerY);
        pos++;
    }

    printf("\nWriting: %lu\n", sizeof(IEntity::Entity2File) * entitiesVect.size());
    file.write(reinterpret_cast<const char*>(sts), sizeof(IEntity::Entity2File) * entitiesVect.size());

    file.close();
    // Free up memory
    delete[] sts;
}

/**
 * Loads the entities from a binary file
 * @param filePath
 */
void EntityManager::loadEntitiesFromFile(const std::string& filePath) {
   std::ifstream infile(filePath, std::ios::binary);
    printf("Clearing all entities first");
    entities[0].clear();
    printf("\nLoading entities...\n");
   // determine the size of the file
   infile.seekg(0, std::ios::end);
   std::streampos size = infile.tellg();
   infile.seekg(0, std::ios::beg);

   // determine the size of the array
   size_t num_sts = size / sizeof(IEntity::Entity2File);
    printf("\nTotal of entities: %ld\n", num_sts);

   // create an array of structs
   auto* sts = new IEntity::Entity2File[num_sts];

   // read the array data from the file
   infile.read(reinterpret_cast<char*>(sts), size);

   // close the file
   infile.close();

   // iterate the array data
   for (int i = 0; i < num_sts; ++i) {
       auto entityStuct = sts[i];
       auto regShape = new RegularShape(fvec2{entityStuct.centerX, entityStuct.centerY}, entityStuct.radius, entityStuct.div, entityStuct.ang);
       regShape->setToColor(entityStuct.r, entityStuct.g, entityStuct.b);
       entities[0].push_back(regShape);
   }

   // free the memory
   delete[] sts;
}

