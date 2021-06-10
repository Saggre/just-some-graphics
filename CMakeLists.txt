# Ignore compiler checks (required on cross-platform compilation)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(PROJECT_NAME "just-some-graphics")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Projects Settings
cmake_minimum_required(VERSION 3.7)
project(just-some-graphics)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_STANDARD 17)
set(SHADERS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/shader")

# Create embedded shaders file
add_custom_target(
        embed_shader
        COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/embed_shaders.sh ${PROJECT_SOURCE_DIR}/src/embed_shader.hpp ${SHADERS_SOURCE_DIR}
)

# The main executable
add_executable(${PROJECT_NAME}
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

add_dependencies(${PROJECT_NAME} embed_shader)
include_directories(${PROJECT_SOURCE_DIR})

if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE GLVND)
endif ()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)

# GLEW
target_include_directories(${PROJECT_NAME} PUBLIC lib/GLEW/include)
add_library(glew32 STATIC IMPORTED GLOBAL)

if (WIN32)
    set_target_properties(glew32 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/lib/libglew32.a)
else ()
    set_target_properties(glew32 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/lib64/libGLEW.a)
endif ()

set_target_properties(glew32 PROPERTIES INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glew32)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC opengl32)
else ()
    target_link_libraries(${PROJECT_NAME} PUBLIC GL)
endif ()

# SDL2
target_include_directories(${PROJECT_NAME} PRIVATE lib/SDL/include)
execute_process(
        COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL/bin/sdl2-config --static-libs"
        OUTPUT_VARIABLE SDLFLAGS
)
string(STRIP ${SDLFLAGS} SDLFLAGS)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDLFLAGS})

# Include MathFu in this project with test and benchmark builds disabled
# then add MathFu compiler flags to the mygame build target.
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
mathfu_configure_flags(${PROJECT_NAME})
