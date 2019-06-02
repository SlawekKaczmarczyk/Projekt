#pragma once


#include <thread>
#include "Simulation.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "json.hpp"

using json = nlohmann::json;

class SimulationControl {
public:
    SimulationControl(Simulation &simulation, int port);

    void connect();

    ~SimulationControl();

    std::string receive_cmd();

    // send array of alive cells (x,y) to client
    void sendBoardData();
    void sendStats();
private:
    /// Listens for commands from client in JSON format
    void listen();

    Simulation &simulation;
    std::thread command_thread;
    int port;
    int socket_fd;
    sockaddr_in address;
};



