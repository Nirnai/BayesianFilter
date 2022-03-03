cmake_minimum_required(VERSION 3.2)

project(
  BayesianFilter
  VERSION 0.1
  LANGUAGES CXX)

  # set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
  # set(CMAKE_CXX_STANDARD_REQUIRED ON)
  # set(CMAKE_CXX_EXTENSIONS OFF)

  # find_package (Eigen3 3.3 REQUIRED NO_MODULE)

  include_directories(${PROJECT_SOURCE_DIR}/include)

  add_executable(main src/main.cpp)
  target_link_libraries (main)
  target_compile_features(main PRIVATE cxx_std_20)

  ## Testing
  # option(BUILD_TEST "Build unit tests" ON)
  # if(BUILD_TEST)
  #   enable_testing()
  #   add_subdirectory(test)
  # endif()
