#pragma once
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include "cmake-build-debug/Gate.h"
#include <unordered_map>

class Simulation {
public:
    /// Creates Game of Life simulation
    /// @param [in] width Width of board (cells)
    /// @param [in] height Height of board
    /// @param [in] framerate Delay between generations in microseconds
    Simulation(size_t width, size_t height, size_t framerate);


    /// Insert or remove cell
    void setAlive(size_t x, size_t y, bool alive);
    bool isAlive(size_t x, size_t y);

    void stop();
    void start();
    std::pair<uint32_t, uint32_t> getBoardSize();
    std::vector<bool> getCurrentGeneration();
    uint64_t getGenerationCount();
    ~Simulation();
    void stopSimulation();
    void addRandomCells(size_t count);
private:
    size_t width;
    size_t height;
    /// Simulation loop
    void run();
    void flipGenerations();
    std::atomic_bool exiting = false;
    std::thread simulation_thread;
    std::mutex current_generation_mutex;
    std::pair<uint32_t, uint32_t> board_size;
    size_t generation_count = 0;
    std::atomic<bool> running = true;
    std::vector<bool> current_generation;
    std::vector<bool> next_generation;
    std::unordered_map<std::string,Gate> gates = {{"and",Gate("and.txt")},{"or",Gate("or.txt")}};
};



