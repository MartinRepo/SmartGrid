cmake_minimum_required(VERSION 3.25)
project(SmartGrid)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/googletest)
enable_testing()
include(GoogleTest)

include_directories(/opt/homebrew/Cellar/cpprestsdk/2.10.19/include /opt/homebrew/Cellar/boost/1.84.0_1/include /opt/homebrew/Cellar/openssl@3/3.2.1/include)
link_directories(/opt/homebrew/Cellar/cpprestsdk/2.10.19/lib /opt/homebrew/Cellar/boost/1.84.0_1/lib /opt/homebrew/Cellar/openssl@3/3.2.1/lib)

add_executable(SmartGrid src/main.cpp src/algorithms/FeasibleGraph.cpp src/algorithms/FixedParameterTractable.cpp src/algorithms/Greedy.cpp src/algorithms/Genetic.cpp include/algorithms/FeasibleGraph.h include/algorithms/Genetic.h include/server/api_handler.h src/server/api_handler.cpp include/utils/TotalCost.h src/utils/TotalCost.cpp include/utils/PeakCost.h src/utils/PeakCost.cpp)
add_executable(SmartGridTests tests/TestMain.cpp
        src/algorithms/FeasibleGraph.cpp
        src/algorithms/FixedParameterTractable.cpp
        src/algorithms/Greedy.cpp
        src/algorithms/Genetic.cpp
        src/server/api_handler.cpp
        src/utils/TotalCost.cpp
        src/utils/PeakCost.cpp
        )

target_link_libraries(SmartGrid cpprest boost_system ssl crypto)
target_link_libraries(SmartGridTests gtest_main gmock_main cpprest boost_system ssl crypto)
gtest_discover_tests(SmartGridTests)
