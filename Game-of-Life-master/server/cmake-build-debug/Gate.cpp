#include <iostream>
#include "Gate.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "../Simulation.h"

Gate::Gate(std::size_t width, std::size_t height, std::string filename)
: width(width), height(height)
{

    std::ofstream file( "widthheight.txt", std::ios::out );
    std::string sequence;
    getline( std::cin, sequence);
    file.write( & sequence[ 0 ], sequence.length() );
    while (true) {

        std::cout << "Enter name of file to read from: " << std::endl;
        std::cin >> filename;

        std::ifstream readfile(filename);
        if (readfile.is_open()) {
            std::string fileline, x, y;

            while (getline(readfile, fileline)) {
                std::stringstream ss(fileline);

                getline(ss, x, ' ');
                getline(ss, y, ' ');

                x = stoi(x);
                y = stoi(y);
            }
            break;
        }
    }
}
