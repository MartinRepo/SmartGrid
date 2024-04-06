cmake_minimum_required(VERSION 3.25)
project(SmartGrid)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/Cellar/cpprestsdk/2.10.19/include /opt/homebrew/Cellar/boost/1.84.0_1/include /opt/homebrew/Cellar/openssl@3/3.2.1/include)
link_directories(/opt/homebrew/Cellar/cpprestsdk/2.10.19/lib /opt/homebrew/Cellar/boost/1.84.0_1/lib /opt/homebrew/Cellar/openssl@3/3.2.1/lib)

add_executable(SmartGrid src/main.cpp src/algorithms/FeasibleGraph.cpp src/algorithms/FixedParameterTractable.cpp src/algorithms/Greedy.cpp src/algorithms/Genetic.cpp include/algorithms/FeasibleGraph.h include/algorithms/Genetic.h include/server/api_handler.h src/server/api_handler.cpp tests/TestMain.cpp)

target_link_libraries(SmartGrid cpprest boost_system ssl crypto)