cmake_minimum_required(VERSION 3.25)
project(SmartGrid)

set(CMAKE_CXX_STANDARD 17)

add_executable(SmartGrid src/main.cpp src/algorithms/FeasibleGraph.cpp src/algorithms/FixedParameterTractable.cpp src/algorithms/Greedy.cpp src/algorithms/Genetic.cpp include/algorithms/FeasibleGraph.h include/algorithms/Genetic.h)
