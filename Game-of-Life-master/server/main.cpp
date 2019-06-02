#include <iostream>
#include "Simulation.h"
#include "SimulationControl.h"

int main(int argc, char* argv[]) {
    if(argc < 5){
        std::cout << "Usage: " << argv[0] << "width height delay(us) port\n";
        return 1;
    }
    size_t width = std::atoll(argv[1]);
    size_t height = std::atoll(argv[2]);
    size_t delay = std::atoll(argv[3]);
    size_t port = std::atoll(argv[4]);

    Simulation sim(width, height, delay);
    SimulationControl control(sim, port);

}