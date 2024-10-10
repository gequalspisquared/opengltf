cmake_minimum_required(VERSION 3.15)
project(opengltf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external)

file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/include")

set(SRC_FILES
    # main
    "${SRC_DIR}/main.cpp"

    # Application
    "${INC_DIR}/Application.h"
    "${SRC_DIR}/Application.cpp"

    # Renderer
    "${INC_DIR}/Renderer/IndexBuffer.h"
    "${SRC_DIR}/Renderer/IndexBuffer.cpp"
    "${INC_DIR}/Renderer/Shader.h"
    "${SRC_DIR}/Renderer/Shader.cpp"
    "${INC_DIR}/Renderer/VertexArray.h"
    "${SRC_DIR}/Renderer/VertexArray.cpp"
    "${INC_DIR}/Renderer/VertexBuffer.h"
    "${SRC_DIR}/Renderer/VertexBuffer.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} "${SRC_FILES}")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${INC_DIR}/")
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE RESOURCES_PATH="${PROJECT_SOURCE_DIR}/assets/")
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SHADER_PATH="${PROJECT_SOURCE_DIR}/shaders/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glm imgui tinygltf stb glad fmt::fmt)
