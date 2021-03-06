# Ignore compiler checks (required on cross-platform compilation)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(PROJECT_NAME "just-some-graphics")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Projects Settings
cmake_minimum_required(VERSION 3.7)
project(
        just-some-graphics
        DESCRIPTION "Just some graphics"
        HOMEPAGE_URL "https://github.com/Saggre"
)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_STANDARD 17)
set(SHADERS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/shader")

# Create embedded shaders file
add_custom_target(
        embed_shader
        COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/embed_shaders.sh ${PROJECT_SOURCE_DIR}/src/embed_shader.hpp ${SHADERS_SOURCE_DIR}
)

include_directories("${PROJECT_SOURCE_DIR}/lib/win")
if (WIN32)
    add_library(SDL2_image SHARED IMPORTED GLOBAL)
    set_target_properties(SDL2_image PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/win/SDL2_image.dll)
endif ()

set(SOURCE_FILES src/main.cpp
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
        src/core/functions/core.hpp
        src/core/functions/print.hpp)

# The main executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} embed_shader)
include_directories(${PROJECT_SOURCE_DIR})

# Clone textures
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures)

if (WIN32)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
endif ()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
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

target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/SDL2)

# SDL2_image
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/lib/win"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
endif ()

# Include MathFu in this project with test and benchmark builds disabled
# then add MathFu compiler flags to the mygame build target.
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
mathfu_configure_flags(${PROJECT_NAME})
