// Serial_Port.cpp
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#include "SerialPort.h"

using namespace std;
using namespace boost;

// Function to read data from the serial port
string SerialPort::readFromSerialPort(asio::serial_port& serial)
{
    char buffer[100]; // Buffer to store incoming data
    system::error_code ec;
    // Read data from the serial port
    size_t len
        = asio::read(serial, asio::buffer(buffer), ec);
    if (ec) {
        cerr << "Error reading from serial port: "
            << ec.message() << endl;
        return "";
    }
    // Return the read data as a string
    return string(buffer, len);
}

// Function to configure the serial port
void SerialPort::configureSerialPort(asio::serial_port& serial, const string& portname, unsigned int baud_rate)
{
    // Open the specified serial port
    serial.open(portname);
    // Set the baud rate
    serial.set_option(
        asio::serial_port_base::baud_rate(baud_rate));
}

// Function to write data to the serial port
void SerialPort::writeToSerialPort(asio::serial_port& serial, const string& message)
{
    system::error_code ec;
    // Write data to the serial port
    asio::write(serial, asio::buffer(message), ec);
    if (ec) {
        cerr << "Error writing to serial port: "
            << ec.message() << endl;
    }
}

