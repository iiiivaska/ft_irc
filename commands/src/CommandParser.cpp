#include "../includes/CommandParser.hpp"

Command *CommandParser::parseCommand(std::string const &command) {
	int pos = command.find(' ');
	std::string cmd = command.substr(0, pos);

	if (!isCommand(cmd))
		throw std::invalid_argument("Not a command!");

	std::string params = command.substr(++pos);
	return new Command(cmd, params);
}

bool CommandParser::isCommand(std::string cmd) {
	bool result = false;

	for (int i = 0; i < commandPool.size(); i++) {
		if (commandPool[i] == cmd)
			result = true;
	}
	return result;
}

CommandParser::CommandParser() {
	commandPool.push_back("PASS");
	commandPool.push_back("NICK");
	commandPool.push_back("USER");
	commandPool.push_back("QUIT");

	commandPool.push_back("PING");
	commandPool.push_back("JOIN");
	commandPool.push_back("PART");

	commandPool.push_back("PRIVMSG");
}


CommandParser::~CommandParser() {
	commandPool.clear();
}