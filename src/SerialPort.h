// Serial_Port.h
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>
#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class SerialPort
{
public:
	string readFromSerialPort(asio::serial_port& serial);
	void configureSerialPort(asio::serial_port& serial, const string& portname, unsigned int baud_rate);
	void writeToSerialPort(asio::serial_port& serial, const string& message);
};

#endif
