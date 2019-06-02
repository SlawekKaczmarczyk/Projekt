#pragma once
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>

class Gate {
public:
    Gate(std::size_t x, std::size_t y, std::string filename);
    void drawGate(Gate& gate, int x, int y);
    Gate(const char string[]);

private:
    size_t width;
    size_t height;
    std::string filename;
    int x;
    int y;
};


