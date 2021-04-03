//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_ENTITY_HPP_
#define JUST_SOME_GRAPHICS_SRC_ENTITY_HPP_

#include <vector>

#include "src/core/abstract_updatable.hpp"
#include "src/core/components/component.hpp"
#include "src/core/components/transform.hpp"

/**
 * Base class for all movable objects
 */
class Entity : public AbstractUpdatable {
 public:
  Transform transform_;

  void AddComponent(Component *component) {
    components_.push_back(component);
  }

  void Start() override {
    components_.push_back(&transform_);

    for (auto &component : components_) {
      component->Init(this, &transform_);
      component->Start();
    }
  }

  void Update() override {
    for (auto &component : components_) {
      component->Update();
    }
  }

  void End() override {
    for (auto &component : components_) {
      component->End();
    }
  }

 private:
  AbstractUpdatable *parent_;
  std::vector<Entity *> children_;
  std::vector<Component *> components_;
};

#endif //JUST_SOME_GRAPHICS_SRC_ENTITY_HPP_
