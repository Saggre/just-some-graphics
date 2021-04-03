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

  /**
   * Constructor
   */
  explicit MultiFrameData(T initial) {
    current_frame_ = initial;
    Update(initial);
  }

  /**
   * Provide a custom delta calculation formula
   * @param delta_calc
   */
  explicit MultiFrameData(T initial, DeltaCalc delta_calc) {
    delta_calc_ = delta_calc;
    current_frame_ = initial;
    Update(initial);
  }

  /**
   * Get current-frame value
   * @return
   */
  T GetCurrent() const {
    return current_frame_;
  }

  /**
   * Get last-frame value
   * @return
   */
  T GetLast() const {
    return last_frame_;
  }

  /**
   * Get current-last frame delta
   * @return
   */
  T GetDelta() const {
    return delta_;
  }

  /**
   * Update with a new value. Should be called on every reference frame
   * @param new_frame
   */
  void Update(T new_frame) {
    last_frame_ = current_frame_;
    current_frame_ = new_frame;
    delta_ = delta_calc_(current_frame_, last_frame_);
  }

 protected:
  /**
   * Default delta calculation formula
   */
  DeltaCalc delta_calc_ = [](T current, T last) {
    return current - last;
  };

  T current_frame_;
  T last_frame_;
  T delta_;
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_MULTI_FRAME_DATA_HPP_
