#include <iostream>
#include <random>
#include <unordered_set>
#include "Simulation.h"
#include "cmake-build-debug/Gate.h"

Simulation::Simulation(std::size_t width, std::size_t height, std::size_t framerate)
: width(width), height(height)
{
    current_generation.resize(width*height, false);
    next_generation.resize(width*height, false);
    board_size = {width, height};
    addRandomCells(10000);
    simulation_thread = std::thread(&Simulation::run, this);
}

void Simulation::stop() {

}

void Simulation::start() {

}

void Simulation::setAlive(size_t x, size_t y, bool alive) {
    if(x >= width || x < 0)
        throw std::invalid_argument("x");
    if(y >= width || y < 0)
        throw std::invalid_argument("y");

    next_generation[y*width + x] = alive;
}
bool Simulation::isAlive(size_t x, size_t y) {
    if(x >= width || x < 0)
        return false;
    if(y >= width || y < 0)
        return false;

    return current_generation[y*width + x];
}



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void Simulation::run() {
    while(!exiting){
        while(!running){
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            if(exiting) {
                std::cout << "Simulation: Run thread exiting." << std::endl;
                return;
            }
        }

        for(size_t x = 0; x < width; x++){
            for(size_t y = 0; y < height; y++){
                int neighbours = 0;
                if(isAlive(x-1, y-1)) neighbours++;
                if(isAlive(x, y-1)) neighbours++;
                if(isAlive(x+1, y-1)) neighbours++;
                if(isAlive(x-1, y)) neighbours++;
                if(isAlive(x+1, y)) neighbours++;
                if(isAlive(x-1, y+1)) neighbours++;
                if(isAlive(x, y+1)) neighbours++;
                if(isAlive(x+1, y+1)) neighbours++;

                if(neighbours < 2 || neighbours > 3)setAlive(x, y, false);
                if(neighbours == 3 && !isAlive(x,y))setAlive(x, y, true);
            }

        }
        flipGenerations();
        generation_count++;
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));



    }
}
#pragma clang diagnostic pop



std::vector<bool> Simulation::getCurrentGeneration() {
    current_generation_mutex.lock();
    std::vector<bool> result = current_generation;
    current_generation_mutex.unlock();
    return result;
}

std::pair<uint32_t, uint32_t> Simulation::getBoardSize() {
    return board_size;
}

Simulation::~Simulation() {
    if(simulation_thread.joinable())
        simulation_thread.join();
}

void Simulation::stopSimulation() {
    exiting = true;
}

void Simulation::addRandomCells(size_t count) {
    std::random_device dev;
    std::mt19937 rng(dev());

    struct pair_hash {
        inline std::size_t operator()(const std::pair<int,int> & v) const {
            return v.first*31+v.second;
        }
    };

    std::unordered_set<std::pair<int,int>, pair_hash> coords{};
    while(coords.size() < count){
        coords.insert({static_cast<int>(rng() % width), static_cast<int>(rng() % height)});
    }
    for(auto pair : coords){
        setAlive(pair.first, pair.second, true);
    }

    flipGenerations();
}

void Simulation::flipGenerations() {
    current_generation_mutex.lock();
    current_generation = next_generation;
    current_generation_mutex.unlock();
}

uint64_t Simulation::getGenerationCount() {
    return generation_count;


}
void drawGate(Gate& gate, int x, int y) {

}

