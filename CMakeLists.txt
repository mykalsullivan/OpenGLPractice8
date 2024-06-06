cmake_minimum_required(VERSION 3.28)
project(OpenGLPractice8)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)

add_executable(OpenGLPractice8
        src/main.cpp
        src/window.cpp
        src/mesh.cpp
        src/shader.cpp
        src/camera.cpp
)

target_link_libraries(OpenGLPractice8
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}

)
