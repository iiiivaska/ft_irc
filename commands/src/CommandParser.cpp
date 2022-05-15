#include "../includes/CommandParser.hpp"

Command *CommandParser::parseCommand(std::string const &strCommand) {
	std::string newStr = strCommand;
	newStr.pop_back();

	std::string command = skipStartSpaces(newStr);
	int pos = command.find(' ');
	std::string cmd = command.substr(0, pos);

	if (!isCommand(cmd))
		throw std::invalid_argument("Not a command!");

	std::string params = command.substr(++pos);
	Command *currentCmd = new Command(cmd, params);

	isValid(currentCmd);
	return currentCmd;
}

bool CommandParser::isCommand(const std::string &cmd) {
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
	commandPool.push_back("KICK");
	commandPool.push_back("PRIVMSG");
}


CommandParser::~CommandParser() {
	commandPool.clear();
}

std::string CommandParser::skipStartSpaces(const std::string &str) {
	int pos = 0;
	std::string token = str;

	for (int i = 0; i < token.size() && std::isspace(str[i]); ++i)
		pos++;
	token.erase(0, pos);
	return token;
}

void CommandParser::isValid(Command *cmd) const {
	if (cmd->getCountParams() > MAX_PARAM)
		throw std::invalid_argument("Maximum params should be 15");
	else if (cmd->getMessage().size() > MAX_LEN)
		throw std::invalid_argument("Maximum message size should be 510");
}
