#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <string>
#include <iostream>
#include <map>
#include "Command.hpp"

class CommandParser {
private:
	int MAX_LEN = 512;
	int MAX_PARAM = 15;
	std::string name;
	std::vector<std::string> commandPool;

	bool isCommand(std::string cmd);
public:
	CommandParser();
	~CommandParser();

	Command *parseCommand(std::string const &command);

};

#endif
