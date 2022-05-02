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
public:
	Command(const std::string& name, std::string params);
	~Command();
	std::string getName();
	std::string getMessage();
	size_t getCountParams();
	std::vector<std::string> getParams();
};

#endif
