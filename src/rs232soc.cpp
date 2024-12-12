// rs232soc.cpp
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <cstdio>

#include "SerialPort.h"
#include "InputParser.h"
#include "Listener.h"

void parseArguments(InputParser input);
void killProcessWithArgumentException(string e);
bool fileExists(const std::string& filePath);

string sPort;
string logDestination;
string listenerAddress;
string listenerPort;
string listenerThreads{"1"};

int baud{ 9600 };
char errstr[512];

int main(int argc, char* argv[])
{
    asio::io_service io; // Create an IO service
    asio::serial_port serial(io); // Create a serial port object
    SerialPort serialPort;

    InputParser input(argc, argv); //parse arguments and set variables
    parseArguments(input);

    auto const address = net::ip::make_address(listenerAddress.c_str());
    auto const port = static_cast<unsigned short>(std::atoi(listenerPort.c_str()));
    auto const threads = std::max<int>(1, std::atoi(listenerThreads.c_str()));

    std::cout << "Set Serial Listener to Port " << sPort << " with " << baud << " baud" << endl;
    try {
        serialPort.configureSerialPort(serial, sPort, baud);
    }
    catch (const std::exception& e) {
        std::cout << "Please check configuration - the port you choosed might not exists" << endl;
        return 1;
    }

    net::io_context ioc{ threads };
    std::make_shared<Listener>(ioc, tcp::endpoint{ address, port }, serial, serialPort )->run();

    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for (auto i = threads - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
    ioc.run();

    return EXIT_SUCCESS;

    serial.close();
};

void parseArguments(InputParser input) {

    if (input.cmdOptionExists("-log") && input.getCmdOption("-log").length() <= 256) {
        logDestination = input.getCmdOption("-log");
        std::cout << "Write to log: " << logDestination << endl;
    }

    if (input.cmdOptionExists("-a") && input.getCmdOption("-a").length() <= 256) {
        listenerAddress = input.getCmdOption("-a");
        std::cout << "Listen on address: " << listenerAddress << endl;
    }

    if (input.cmdOptionExists("-t") && input.getCmdOption("-t").length() <= 256) {
        listenerThreads = input.getCmdOption("-t");
        std::cout << "Count of listener threads: " << listenerThreads << endl;
    }

    if (input.cmdOptionExists("-p") && input.getCmdOption("-p").length() <= 256) {
        listenerPort = input.getCmdOption("-p");
        std::cout << "Listen on address port: " << listenerPort << endl;
    }

    if (input.cmdOptionExists("-sp")) {
        sPort = input.getCmdOption("-sp");
        std::cout << "Lookup on port: " << sPort << endl;
    }
    else {
        killProcessWithArgumentException("No -p (serial device) given or to long");
    }
}

void killProcessWithArgumentException(string e) {
    std::cout << e << endl;
    std::cout << "Please check arguments - abort!" << endl;
    exit(1);
}

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}
