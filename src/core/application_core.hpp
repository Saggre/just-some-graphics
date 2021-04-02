#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP

#include "input_manager.hpp"
#include "abstract_updatable.hpp"

#include <string>
#include <iostream>
#include <vector>

struct GLFWwindow;

class ApplicationCore {
 public:
  ApplicationCore();

  static ApplicationCore &getInstance();

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
   * Get delta time between frame and time from beginning
   * @return
   */
  float GetFrameDeltaTime() const;

  /**
   * Get current running time
   * @return
   */
  float GetTime() const;

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

  float time;
  float delta_time;

  int width;
  int height;
  bool dimension_changed;
  void DetectWindowDimensionChange();

 protected:
  // ApplicationCore(const ApplicationCore &);

  InputManager input_manager;
  std::string title;
  bool fullscreen = false;

  virtual void Loop();
};

#endif
