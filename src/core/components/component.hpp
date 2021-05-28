//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_COMPONENT_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_COMPONENT_HPP_

#include "../abstract_updatable.hpp"

class Transform;
class Entity;

class Component : public AbstractUpdatable {
 public:
  Entity *parent = nullptr;
  Transform *transform = nullptr;

  void Init(Entity *p, Transform *t) {
    this->parent = p;
    this->transform = t;
  };

  void Start() override {

  }

  void Update() override {

  }

  void End() override {

  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_COMPONENT_HPP_
