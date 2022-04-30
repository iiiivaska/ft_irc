#include "utilities.hpp"

std::vector<std::string> split(std::string str, std::string delimiter) {
	size_t pos = 0;
	std::string token;
	std::vector<std::string> arr;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		arr.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	return arr;
}
