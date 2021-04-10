#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP

#include "input_manager.hpp"
#include "abstract_updatable.hpp"
#include "time.hpp"

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

  ApplicationCore() : state(stateReady), title("ApplicationCore") {
    currentApplication = this;

    dimension_changed = false;

    std::cout << "[Info]: GLFW initialisation" << std::endl;

    // initialize the GLFW library
    if (!glfwInit()) {
      throw std::runtime_error("Couldn't init GLFW");
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);

    width = vidMode->width;
    height = vidMode->height;

    if (!fullscreen) {
      width = 1000;
      height = 600;
    }

    // setting the opengl version
    int major = 4;
    int minor = 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window
    window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? monitor : nullptr, nullptr);

    if (!window) {
      glfwTerminate();
      throw std::runtime_error("Couldn't create a window");
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (glfwRawMouseMotionSupported()) {
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK) {
      glfwTerminate();
      throw std::runtime_error(std::string("Could initialize GLEW, error = ") +
          (const char *) glewGetErrorString(err));
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    // glfwSwapInterval(false);
  }

  static ApplicationCore &getInstance() {
    if (currentApplication) {
      return *currentApplication;
    } else {
      throw std::runtime_error("There is no current ApplicationCore");
    }
  }

  bool IsEngineFlag(EngineFlag flag) {
    return engine_flags_.test(flag);
  }

  /**
   * Get window id
   * @return
   */
  GLFWwindow *GetWindow() const {
    return window;
  }

  /**
   * Close window
   */
  void Exit() {
    state = stateExit;
  }

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
  void Run() {
    state = stateRun;

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetTime(0);

    Start();

    while (state == stateRun) {
      auto time = (float) glfwGetTime();
      Time::SetTime(time);

      // detech window related changes
      DetectWindowDimensionChange();

      // execute the frame code
      Loop();

      // Swap Front and Back buffers (double buffering)
      glfwSwapBuffers(window);

      // Pool and process events
      glfwPollEvents();
    }

    glfwTerminate();
  }

  /**
   * Get window width in pixels
   * @return
   */
  int getWidth() const {
    return width;
  }

  /**
   * Get window height in pixels
   * @return
   */
  int getHeight() const {
    return height;
  }

  /**
   * Get window aspect ratio
   * @return
   */
  float GetWindowRatio() const {
    return float(width) / float(height);
  }

  void AddEntity(AbstractUpdatable *entity) {
    entities_.push_back(entity);
  }

  bool windowDimensionChanged() {
    return dimension_changed;
  }

 private:
  enum State { stateReady, stateRun, stateExit };

  State state;

  ApplicationCore &operator=(const ApplicationCore &) { return *this; }

  GLFWwindow *window;

  std::vector<AbstractUpdatable *> entities_;
  std::vector<int> test_;

  inline static Time time_;

  std::bitset<64> engine_flags_;

  int width;
  int height;
  bool dimension_changed;

  void DetectWindowDimensionChange() {
    int w, h;
    glfwGetWindowSize(GetWindow(), &w, &h);
    dimension_changed = (w != width or h != height);
    if (dimension_changed) {
      width = w;
      height = h;
      glViewport(0, 0, width, height);
    }
  }

  void SetEngineFlag(EngineFlag flag, bool state = true) {
    engine_flags_.set(flag, state);
  }

 protected:
  // ApplicationCore(const ApplicationCore &);
  inline static ApplicationCore *currentApplication = nullptr;
  InputManager input_manager;
  std::string title;
  bool fullscreen = true;

  virtual void Loop() {
    if (!IsEngineFlag(InputEnabledOnce) && Time::time_ > 0.5) {
      InputManager::SetMouseEnabled(true);
      SetEngineFlag(InputEnabledOnce);
    }

    input_manager.Update();

    // Reference to a pointer
    for (auto &entity : entities_) {
      entity->Update();
    }

    if (InputManager::IsKeyDown(InputManager::Down)) {
      std::cout << "Keypress\n";
    }

    if (InputManager::IsKeyDown(InputManager::Esc)) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }

  virtual void Start() {
    input_manager.Init(window);
  }
};

#endif
