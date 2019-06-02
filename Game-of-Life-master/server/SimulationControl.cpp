#include <cstring>
#include <libnet.h>
#include <iostream>
#include "SimulationControl.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void SimulationControl::listen() {
    while(true){
        auto cmd = receive_cmd();
        if(cmd.empty())
            break;

        std::cout << "CMD: " << cmd << std::endl;
        json cmd_json = json::parse(cmd);
        if(!cmd_json.contains("cmd"))
            throw std::runtime_error("Invalid command from client");

        // handle data request
        if(cmd_json["cmd"] == std::string("data")){
            sendBoardData();
        }else if(cmd_json["cmd"] == std::string("stats")){
            sendStats();
        }

    }
    simulation.stopSimulation();
    std::cout << "SimulationControl: Listen thread exiting." << std::endl;

}
#pragma clang diagnostic pop

void SimulationControl::connect() {
    if (::connect(socket_fd, reinterpret_cast<const sockaddr *>(&address), sizeof(address))) {
        throw std::runtime_error(std::strerror(errno));
    }
}

SimulationControl::SimulationControl(Simulation &simulation, int port)
        : simulation(simulation), port(port) {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr = {};
    inet_aton("127.0.0.1", &address.sin_addr);
    connect();
    command_thread = std::thread(&SimulationControl::listen, this);

}

SimulationControl::~SimulationControl() {
    if(command_thread.joinable())
        command_thread.join();
    close(socket_fd);
}

std::string SimulationControl::receive_cmd() {
    uint64_t size = 0;
    std::string buffer;
    // get size of command
    recv(socket_fd, &size, sizeof(size), 0);
    buffer.resize(size);
    // get json command
    recv(socket_fd, buffer.data(), size, 0);
    return buffer;
}

void SimulationControl::sendBoardData() {

    auto generation = simulation.getCurrentGeneration();
    uint16_t x = 0, y = 0;
    std::vector<uint32_t> data;
    for(bool cell : generation){
        if(cell){
            data.push_back(x);
            data.push_back(y);
        }
        if(++x == simulation.getBoardSize().first){
            x = 0;
            y++;
        }
    }

    // send size of incoming data in bytes
    uint64_t size = data.size() * sizeof(uint32_t);
    send(socket_fd, &size, sizeof(size), 0);
    // send alive cells
    send(socket_fd, data.data(), size, 0);

}

void SimulationControl::sendStats() {
    json stats = {
        {"generation", simulation.getGenerationCount()}
    };
    std::string to_send = stats.dump();
    // send size of incoming data in bytes
    uint64_t size = to_send.size();
    send(socket_fd, &size, sizeof(size), 0);

    // send stats
    send(socket_fd, to_send.data(), size, 0);
}
