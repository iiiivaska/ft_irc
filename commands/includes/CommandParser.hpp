#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <string>
#include <iostream>
#include <map>
#include <cctype>
#include <cstdlib>
#include "Command.hpp"

class CommandParser {
private:
	int MAX_LEN = 512;
	int MAX_PARAM = 15;
	std::string name;
	std::vector<std::string> commandPool;
	std::string skipStartSpaces(const std::string &str);
	bool isCommand(const std::string& cmd);
	void isValid(Command *cmd) const;
public:
	CommandParser();
	~CommandParser();
	Command *parseCommand(std::string const &command);
};

#endif
