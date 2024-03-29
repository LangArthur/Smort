cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
project(test)

set(CMAKE_BUILD_TYPE "Debug")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG        45ce5ddd197d5c58f50fdd3296a5131c894e5527 # release-3.3.7
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG        bf71a834948186f4097caa076cd2663c69a10e1e # 0.9.9.8
)
FetchContent_MakeAvailable(glm)

add_subdirectory(GLToolbox)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/Seek.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/Flee.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/SteeringAlgorithm.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    include/
    GLToolbox/include/
)

## Linking libraries to street
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
    glm::glm
    glfw
    glut
    GLToolBox
)

# movement example
add_executable(movement-example
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/movement/movement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/utils/TestScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/Flee.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/Seek.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/SteeringAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/Arrive.cpp
)

target_include_directories(movement-example PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    include/
    GLToolbox/include/
    examples/
)

## Linking libraries to street
target_link_libraries(movement-example PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
    glm::glm
    glfw
    glut
    GLToolBox
)