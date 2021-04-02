//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_ABSTRACTUPDATABLE_HPP_
#define JUST_SOME_GRAPHICS_SRC_ABSTRACTUPDATABLE_HPP_

/**
 * Base class for all objects that are continuously updated
 */
class AbstractUpdatable {
 public:
  /**
   * Runs once on render loop start
   */
  virtual void Start() = 0;

  /**
   * Runs on every rendered frame
   */
  virtual void Update() = 0;

  /**
   * Runs once after the last rendered frame
   */
  virtual void End() = 0;
};

#endif //JUST_SOME_GRAPHICS_SRC_ABSTRACTUPDATABLE_HPP_