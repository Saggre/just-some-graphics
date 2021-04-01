# Projects Settings
cmake_minimum_required(VERSION 3.1)
project(just-some-graphics)

set(SHADERS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/shader")

add_custom_target(
        embed_shader
        COMMAND bash ${PROJECT_SOURCE_DIR}/embed.sh ${PROJECT_SOURCE_DIR}/src/embed_shader.hpp ${SHADERS_SOURCE_DIR}
)

# The main executable
add_executable(main
        src/application_core.cpp
        src/application_core.cpp
        src/application.cpp
        src/application.cpp
        src/gl_error.hpp
        src/gl_error.cpp
        src/main.cpp
        src/shader.hpp
        src/shader.cpp
        src/abstract_updatable.hpp)

add_dependencies(main embed_shader)

set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)
