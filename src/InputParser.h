//InputParser.h
//Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#pragma once
#include <vector>
#include <string>
#include <algorithm>
class InputParser
{
	public:
		InputParser(int& argc, char** argv);
		const std::string& getCmdOption(const std::string& option) const;
		bool cmdOptionExists(const std::string& option) const;
	private:
		std::vector <std::string> tokens;
};

#endif

