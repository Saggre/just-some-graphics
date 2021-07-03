#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_CORE_HPP

#include "input_manager.hpp"
#include "abstract_updatable.hpp"
#include "time.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include <GL/glew.h>

class ApplicationCore {
 public:
  enum EngineFlag {
    None = 0,
    InputEnabledOnce = 1
  };

  SDL_Window *window;

  ApplicationCore() : state(stateReady), title("ApplicationCore") {
    instance = this;
    dimension_changed = false;

    std::cout << "[Info]: SDL initialisation" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
      SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
      return;
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    width = DM.w;
    height = DM.h;

    fullscreen = true;
    if (!fullscreen) {
      width = 1000;
      height = 600;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    // Create a window
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_SetWindowTitle(window, "Just some graphics");

    if (!window) {
      SDL_Quit();
      throw std::runtime_error("Couldn't create a window");
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    context = SDL_GL_CreateContext(window);

    if (context == nullptr) {
      printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
    }

    renderer = nullptr;
    /*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
      std::cout << "Error creating renderer: " << SDL_GetError() << '\n';
      SDL_Quit();
    }*/

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK) {
      SDL_Quit();
      throw std::runtime_error(std::string("Could initialize GLEW, error = ") +
          (const char *) glewGetErrorString(err));
    }

    const GLubyte *gl_renderer = glGetString(GL_RENDERER);
    const GLubyte *gl_version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << gl_renderer << std::endl;
    std::cout << "OpenGL version supported " << gl_version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
  }

  /**
   * Get core instance
   * @return
   */
  static ApplicationCore &Instance() {
    if (instance) {
      return *instance;
    } else {
      throw std::runtime_error("There is no current ApplicationCore instance");
    }
  }

  bool IsEngineFlag(EngineFlag flag) {
    return engine_flags_.test(flag);
  }

  /**
   * Get window id
   * @return
   */
  SDL_Window *GetWindow() const {
    return window;
  }

  /**
   * Close the window
   */
  void Exit() {
    state = stateExit;
  }

  /**
   * Get current running time in seconds
   * @return
   */
  float GetTime() {
    return static_cast<float>(SDL_GetTicks()) * 0.001;
  }

  /**
   * Get current delta time in seconds
   * @return
   */
  float GetDeltaTime() {
    return static_cast<float>(frame_times.GetDelta()) * 0.001;
  }

  /**
   * Run application
   */
  void Run() {
    state = stateRun;

    Start();

    while (state == stateRun) {
      auto time = GetTime();
      Time::SetTime(time);

      // Detect window related changes
      DetectWindowDimensionChange();

      // Execute frame
      Loop();
    }

    SDL_Quit();
    End();
  }

  /**
   * Get window width in pixels
   * @return
   */
  int GetWidth() const {
    return width;
  }

  /**
   * Get window height in pixels
   * @return
   */
  int GetHeight() const {
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

  bool WindowDimensionChanged() const {
    return dimension_changed;
  }

 private:
  enum State { stateReady, stateRun, stateExit };
  State state;
  ApplicationCore &operator=(const ApplicationCore &) { return *this; }
  SDL_Renderer *renderer;
  SDL_GLContext context;

  std::vector<AbstractUpdatable *> entities_;
  std::bitset<64> engine_flags_;

  int width;
  int height;
  bool dimension_changed;

  void DetectWindowDimensionChange() {
    int w, h;
    SDL_GetWindowSize(GetWindow(), &w, &h);
    dimension_changed = (w != width or h != height);
    if (dimension_changed) {
      width = w;
      height = h;
      glViewport(0, 0, width, height);
    }
  }

  void SetEngineFlag(EngineFlag flag, bool flag_state = true) {
    engine_flags_.set(flag, flag_state);
  }

 protected:
  inline static ApplicationCore *instance = nullptr;
  InputManager input_manager;
  MultiFrameData<uint32_t> frame_times;
  std::string title;
  bool fullscreen = true;

  virtual void Loop() {
    frame_times.Update(SDL_GetTicks());

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
      if (sdlEvent.type == SDL_QUIT) {
        //..
      } else if (sdlEvent.type == SDL_MOUSEMOTION) {
        auto motion = sdlEvent.motion;
      }
    }

    input_manager.Update();

    glClear(GL_COLOR_BUFFER_BIT);

    if (!IsEngineFlag(InputEnabledOnce) && Time::time_ > 0.5) {
      InputManager::SetMouseEnabled(true);
      SetEngineFlag(InputEnabledOnce);
    }

    // Reference to a pointer
    for (auto &entity : entities_) {
      entity->Update();
    }

    if (InputManager::IsKeyDown(InputManager::Esc)) {
      state = stateExit;
    }

  }

  virtual void Start() {
    input_manager.Init(window);
  }

  /**
   * End runtime
   */
  virtual void End() {

  }
};

#endif
