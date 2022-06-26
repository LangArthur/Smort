cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
project(test)


include(FetchContent)


# OpenglSDK
FetchContent_Declare(
  OpenglSDK
  GIT_REPOSITORY https://github.com/KhronosGroup/OpenCL-SDK
  GIT_TAG        ff44fc38e298ff883716c4cc67a9976eb5205570 # v2022.05.18
)
FetchContent_MakeAvailable(OpenglSDK)

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

# bf71a834948186f4097caa076cd2663c69a10e1e

add_executable(${PROJECT_NAME}
    src/main.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE
    include/
)

## Linking libraries to street
target_link_libraries(${PROJECT_NAME} PUBLIC
  glfw
  glu
)