#include "utilities.hpp"

std::vector<std::string> split(std::string str, const std::string &delimiter) {
	size_t pos = 0;
	std::string token;
	std::vector<std::string> arr;
	while ((pos = str.find(delimiter)) != std::string::npos && str.at(0) != ':') {
		token = str.substr(0, pos);
		if (!token.empty())
			arr.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	return arr;
}
