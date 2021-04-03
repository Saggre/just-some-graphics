//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_TIME_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_TIME_HPP_

class Time {
 public:
  inline static float time_;
  inline static float delta_time_;

  static void SetTime(float time) {
    delta_time_ = time - time_;
    time_ = time;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_TIME_HPP_
