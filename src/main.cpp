#define SDL_MAIN_HANDLED

#include "application.hpp"

int main(int argc, const char *argv[]) {
  Application app;
  app.Run();
  return 0;
}
