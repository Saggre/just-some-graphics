#ifndef OPENGL_CMAKE_SKELETON_APPLICATION_HPP
#define OPENGL_CMAKE_SKELETON_APPLICATION_HPP

#include <string>

struct GLFWwindow;

class ApplicationCore {
 public:
  ApplicationCore();

  static ApplicationCore &getInstance();

  /**
   * Get window id
   * @return
   */
  GLFWwindow *getWindow() const;

  /**
   * Close window
   */
  void exit();

  /**
   * Get delta time between frame and time from beginning
   * @return
   */
  float getFrameDeltaTime() const;

  /**
   * Get current running time
   * @return
   */
  float getTime() const;

  /**
   * Run application
   */
  void run();

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
  float getWindowRatio() const;

  bool windowDimensionChanged() const;

 private:
  enum State { stateReady, stateRun, stateExit };

  State state;

  ApplicationCore &operator=(const ApplicationCore &) { return *this; }

  GLFWwindow *window;

  float time;
  float deltaTime;

  int width;
  int height;
  bool dimensionChanged;
  void detectWindowDimensionChange();

 protected:
  // ApplicationCore(const ApplicationCore &);

  std::string title;

  virtual void loop();
};

#endif
