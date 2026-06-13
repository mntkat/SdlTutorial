cmake_minimum_required(VERSION 3.20)
project(SdlTutorial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
add_subdirectory(SDL3 EXCLUDE_FROM_ALL)

add_executable(SdlTutorial src/main.cpp)

target_link_libraries(SdlTutorial PRIVATE SDL3::SDL3)