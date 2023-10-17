cmake_minimum_required(VERSION 3.27.7)
project(advent-of-code VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

#add_executable(advent-of-code 2022/day1/src/day1.cpp)
#add_executable(advent-of-code 2022/day2/src/day2.cpp)
#add_executable(advent-of-code 2022/day3/src/day3.cpp)
add_executable(advent-of-code 2022/day4/src/day4.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
