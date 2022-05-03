#include "../includes/Command.hpp"

std::string Command::getName() {
	return name;
}

std::vector<std::string> Command::getParams() {
	return param;
}

std::string Command::getMessage() {
	return message;
}

size_t Command::getCountParams() {
	return param.size();
}

Command::~Command() {
	param.clear();
}

Command::Command(const std::string &name, std::string params) {
	this->name = name;
	std::vector<std::string> splitParams = split(params, " ");
	for (std::vector<std::string>::iterator it = splitParams.begin(); it != splitParams.end(); ++it)
		param.push_back(*it);

	splitParams.clear();

	int lastPosition = params.find(":");
	message = params.erase(0, lastPosition + 1);
}
