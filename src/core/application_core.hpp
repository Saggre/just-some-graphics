#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP

#include "input_manager.hpp"
#include "abstract_updatable.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <bitset>

struct GLFWwindow;

class ApplicationCore {
 public:
  enum EngineFlag {
    None = 0,
    InputEnabledOnce = 1
  };

  ApplicationCore();

  static ApplicationCore &getInstance();

  bool IsEngineFlag(EngineFlag flag);

  /**
   * Get window id
   * @return
   */
  GLFWwindow *GetWindow() const;

  /**
   * Close window
   */
  void Exit();

  /**
   * Get current running time
   * @return
   */
  static float GetTime();

  /**
   * Get current delta time
   * @return
   */
  static float GetDeltaTime();

  /**
   * Run application
   */
  void Run();

  /**
   * Get window width in pixels
   * @return
   */
  int getWidth() const;

  /**
   * Get window height in pixels
   * @return
   */
  int getHeight() const;

  /**
   * Get window aspect ratio
   * @return
   */
  float GetWindowRatio() const;

  void AddEntity(AbstractUpdatable *entity);

  bool windowDimensionChanged() const;

 private:
  enum State { stateReady, stateRun, stateExit };

  State state;

  ApplicationCore &operator=(const ApplicationCore &) { return *this; }

  GLFWwindow *window;

  std::vector<AbstractUpdatable *> entities_;
  std::vector<int> test_;

  inline static float time;
  inline static float delta_time;

  std::bitset<64> engine_flags_;

  int width;
  int height;
  bool dimension_changed;
  void DetectWindowDimensionChange();
  void SetEngineFlag(EngineFlag flag, bool state = true);

 protected:
  // ApplicationCore(const ApplicationCore &);

  InputManager input_manager;
  std::string title;
  bool fullscreen = true;

  virtual void Loop();
  virtual void Start();
};

#endif
