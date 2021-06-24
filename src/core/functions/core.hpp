//
// Created by Sakri Koskimies on 6/11/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_FUNCTIONS_CORE_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_FUNCTIONS_CORE_HPP_

inline float GetDeltaTime() {
  return ApplicationCore::Instance().GetDeltaTime();
}

inline float GetTime() {
  return ApplicationCore::Instance().GetTime();
}

#endif //JUST_SOME_GRAPHICS_SRC_CORE_FUNCTIONS_CORE_HPP_
