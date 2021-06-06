# Ignore compiler checks (required on cross-platform compilation)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Projects Settings
cmake_minimum_required(VERSION 3.7)
project(just-some-graphics)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_STANDARD 17)
set(SHADERS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/shader")

add_custom_target(
        embed_shader
        COMMAND bash ${PROJECT_SOURCE_DIR}/embed.sh ${PROJECT_SOURCE_DIR}/src/embed_shader.hpp ${SHADERS_SOURCE_DIR}
)

# The main executable
add_executable(main
        src/main.cpp
        src/application.hpp
        src/core/application_core.hpp
        src/core/gl_error.hpp
        src/core/shader.hpp
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
        src/core/image.hpp
        src/core/util/print.hpp)

add_dependencies(main embed_shader)

if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE GLVND)
endif ()

set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)
target_link_options(main PRIVATE -static-libgcc -static-libstdc++)

# GLEW
target_include_directories(main PUBLIC lib/GLEW/include)
add_library(glew32 STATIC IMPORTED GLOBAL)

if (WIN32)
    set_target_properties(glew32 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/lib/libglew32.a)
else ()
    set_target_properties(glew32 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/lib64/libGLEW.a)
endif ()

set_target_properties(glew32 PROPERTIES INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/include)
target_link_libraries(main PUBLIC glew32)

if (WIN32)
    target_link_libraries(main PUBLIC opengl32)
else ()
    target_link_libraries(main PUBLIC GL)
endif ()

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

# SDL2
target_include_directories(main PRIVATE lib/SDL/include)
execute_process(
        COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL/bin/sdl2-config --static-libs"
        OUTPUT_VARIABLE SDLFLAGS
)
string(STRIP ${SDLFLAGS} SDLFLAGS)
target_link_libraries(main PRIVATE ${SDLFLAGS})

# Include MathFu in this project with test and benchmark builds disabled
# then add MathFu compiler flags to the mygame build target.
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
mathfu_configure_flags(main)
