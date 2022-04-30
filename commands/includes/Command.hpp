
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../utilities/utilities.hpp"

class Command {
private:
	std::string name;
	std::vector<std::string> param;
	std::string message;
	bool parseParams(std::string);
public:
	Command(std::string name, std::string params);
	~Command();
	std::string getName();
	std::vector<std::string> getParams();
};

#endif
