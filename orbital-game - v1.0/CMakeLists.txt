cmake_minimum_required(VERSION 3.15)
project(OrbitalGame CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(orbital_game main.cpp)
target_link_libraries(orbital_game raylib)
