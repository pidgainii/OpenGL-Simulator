cmake_minimum_required(VERSION 3.20)

project(OpenGLSimulator
  VERSION 0.1.0
  LANGUAGES C CXX
)

# -----------------------------
# Options / global settings
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create compile_commands.json (nice for VS Code / clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type (single-config generators like Ninja)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# -----------------------------
# Dependencies
# -----------------------------
include(FetchContent)

# GLM (header-only, via FetchContent)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

# GLFW (from upstream)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# OpenGL (system)
find_package(OpenGL REQUIRED)

# -----------------------------
# GLAD (from your repo)
# -----------------------------
add_library(glad STATIC
  external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)
target_compile_definitions(glad PUBLIC GLAD_GL_IMPLEMENTATION)

# -----------------------------
# Your executable
# -----------------------------
add_executable(simulator
  src/app/main.cpp

  src/core/Application.cpp
  src/core/Engine.cpp
  src/core/Input.cpp

  src/graphics/EBO.cpp
  src/graphics/Renderer.cpp
  src/graphics/ShaderProgram.cpp
  src/graphics/VAO.cpp
  src/graphics/VBO.cpp

  src/io/Loader.cpp
  src/io/ObjLoader.cpp

  src/scene/Mesh.cpp
  src/scene/Renderable.cpp

  src/sim/Simulation.cpp
)

# Your public headers
target_include_directories(simulator PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${glfw_SOURCE_DIR}/include
)
target_link_libraries(simulator PRIVATE
  glfw
  glad
  glm::glm
  OpenGL::GL
)

# On Windows, GLFW needs some system libs depending on toolchain
if(WIN32)
  target_link_libraries(simulator PRIVATE
    gdi32
    user32
    shell32
  )
endif()

# -----------------------------
# Assets (optional convenience)
# -----------------------------
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
add_custom_command(TARGET simulator POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${ASSETS_DIR}
          $<TARGET_FILE_DIR:simulator>/assets
  COMMENT "Copying assets to output folder"
)