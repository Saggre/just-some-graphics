# Projects Settings
cmake_minimum_required(VERSION 3.1)
project(just-some-graphics)

set(CMAKE_CXX_STANDARD 17)
set(SHADERS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/shader")

add_custom_target(
        embed_shader
        COMMAND bash ${PROJECT_SOURCE_DIR}/embed.sh ${PROJECT_SOURCE_DIR}/src/embed_shader.hpp ${SHADERS_SOURCE_DIR}
)

# The main executable
add_executable(main
        src/main.cpp
        src/application.cpp
        src/application.cpp
        src/core/application_core.cpp
        src/core/application_core.cpp
        src/core/gl_error.hpp
        src/core/gl_error.cpp
        src/core/shader.hpp
        src/core/shader.cpp
        src/core/entity.hpp
        src/core/abstract_updatable.hpp
        src/core/components/creative_camera.hpp
        src/core/components/transform.hpp
        src/core/input_manager.hpp
        src/core/multi_frame_data.hpp
        src/core/components/component.hpp
        src/core/components/mesh.hpp
        src/core/time.hpp
        src/core/util/primitive.hpp
        src/core/util/mappings.hpp
        src/core/image.hpp
        src/core/image.hpp)

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

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(main PRIVATE SDL2)

# Include MathFu in this project with test and benchmark builds disabled
# then add MathFu compiler flags to the mygame build target.
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
mathfu_configure_flags(main)
