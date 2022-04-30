#include "../includes/Command.hpp"

std::string Command::getName() {
	return name;
}

std::vector<std::string> Command::getParams() {
	return param;
}

Command::~Command() {
	param.clear();
}

bool Command::parseParams(std::string) {
	return false;
}

Command::Command(std::string name, std::string params) {
	this->name = name;
	std::vector<std::string> splitParams = split(params, " ");
	for (std::vector<std::string>::iterator it = splitParams.begin(); it != splitParams.end(); ++it) {
		param.push_back(*it);
		std::cout << *it << std::endl;
	}
	splitParams.clear();
	std::cout << "--------- size 2 -------------\n" << params.size() << std::endl;

	int lastPosition = params.find(":");
	message = params.erase(0, lastPosition + 1);
}



/**
 std::string s = "scott>=tiger>=mushroom";
std::string delimiter = ">=";

size_t pos = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    std::cout << token << std::endl;
    s.erase(0, pos + delimiter.length());
}
std::cout << s << std::endl;
 * */