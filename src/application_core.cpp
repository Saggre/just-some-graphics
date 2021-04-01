#include "application_core.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

using namespace std;

ApplicationCore *currentApplication = nullptr;

ApplicationCore &ApplicationCore::getInstance() {
  if (currentApplication) {
    return *currentApplication;
  } else {
    throw std::runtime_error("There is no current ApplicationCore");
  }
}

ApplicationCore::ApplicationCore()
    : state(stateReady), title("ApplicationCore") {
  currentApplication = this;

  time = 0.0;
  delta_time = 0.0;
  dimension_changed = false;

  cout << "[Info]: GLFW initialisation" << endl;

  // initialize the GLFW library
  if (!glfwInit()) {
    throw std::runtime_error("Couldn't init GLFW");
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);

  width = vidMode->width;
  height = vidMode->height;

  // setting the opengl version
  int major = 4;
  int minor = 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the window
  window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window");
  }

  glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(win, GLFW_TRUE);
    }
  });

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error(string("Could initialize GLEW, error = ") +
        (const char *) glewGetErrorString(err));
  }

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  cout << "Renderer: " << renderer << endl;
  cout << "OpenGL version supported " << version << endl;

  // opengl configuration
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  // vsync
  // glfwSwapInterval(false);
}

GLFWwindow *ApplicationCore::GetWindow() const { return window; }

void ApplicationCore::Exit() { state = stateExit; }

float ApplicationCore::GetFrameDeltaTime() const { return delta_time; }

float ApplicationCore::GetTime() const { return time; }

void ApplicationCore::Run() {
  state = stateRun;

  // Make the window's context current
  glfwMakeContextCurrent(window);

  time = (float) glfwGetTime();

  while (state == stateRun) {
    // compute new time and delta time
    auto t = (float) glfwGetTime();
    delta_time = t - time;
    time = t;

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

void ApplicationCore::DetectWindowDimensionChange() {
  int w, h;
  glfwGetWindowSize(GetWindow(), &w, &h);
  dimension_changed = (w != width or h != height);
  if (dimension_changed) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
  }
}

void ApplicationCore::Loop() {
  cout << "[INFO]: Run loop\n";
}

int ApplicationCore::getWidth() const { return width; }

int ApplicationCore::getHeight() const { return height; }

float ApplicationCore::GetWindowRatio() const {
  return float(width) / float(height);
}

bool ApplicationCore::windowDimensionChanged() const {
  return dimension_changed;
}
