//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_ENTITY_HPP_
#define JUST_SOME_GRAPHICS_SRC_ENTITY_HPP_

#include "src/core/abstract_updatable.hpp"
#include "transform.hpp"

/**
 * Base class for all movable objects
 */
class Entity : AbstractUpdatable {
 public:
  Entity();
  Transform transform;
  AbstractUpdatable parent;
  std::list<Entity *> children;
};

#endif //JUST_SOME_GRAPHICS_SRC_ENTITY_HPP_
