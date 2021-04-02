//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_MULTI_FRAME_DATA_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_MULTI_FRAME_DATA_HPP_

/**
 * Data that changes from frame-to-frame and we have to keep track of it
 * @tparam T
 */
template<typename T>
class MultiFrameData {
 public:
  typedef T (*DeltaCalc)(T current, T last);

  T GetCurrent() const {
    return current_frame;
  }

  T GetLast() const {
    return last_frame;
  }

  T GetDelta() const {
    return delta;
  }

  explicit MultiFrameData(DeltaCalc delta_calc = DefaultDeltaCalc) {
    delta_calc_ = delta_calc;
    current_frame = T();
    Update(T());
  }

  void Update(T new_frame) {
    last_frame = current_frame;
    current_frame = new_frame;
    delta = delta_calc_(current_frame, last_frame);
  }

 protected:
  DeltaCalc delta_calc_;
  T current_frame;
  T last_frame;
  T delta;

 private:
  static inline T DefaultDeltaCalc(T current, T last) {
    return current - last;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_MULTI_FRAME_DATA_HPP_
