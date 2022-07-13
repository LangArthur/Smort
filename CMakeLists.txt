cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
project(test)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

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

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/movement.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    include/
)

## Linking libraries to street
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glm::glm
    glfw
)