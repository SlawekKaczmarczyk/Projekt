cmake_minimum_required(VERSION 3.13)
project(server)

set(CMAKE_CXX_STANDARD 17)
add_executable(server main.cpp Simulation.cpp Simulation.h SimulationControl.cpp SimulationControl.h cmake-build-debug/Gate.cpp cmake-build-debug/Gate.h)
target_link_libraries(server pthread)
