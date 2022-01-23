cmake_minimum_required(VERSION 3.2)

project(
  BayesianFilter
  VERSION 0.1
  LANGUAGES CXX)

  set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)

  add_executable(main src/main.cpp)