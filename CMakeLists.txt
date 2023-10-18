cmake_minimum_required(VERSION 3.27.7)
project(advent-of-code VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(AOC_YEAR "2022")
set(AOC_DAY "7")

include(CTest)
enable_testing()

add_executable(advent-of-code ${AOC_YEAR}/day${AOC_DAY}/src/day${AOC_DAY}.cpp)
