#include "../includes/CommandParser.hpp"
#include <iostream>

/**
 * Example commands
 * NICK amy
 * WHOIS doctor
 * MODE amy +o
 * JOIN #tardis
 * QUIT
 * */

/**
 * PASS
 * NICK
 * USER
 * PRIVMSG
 * JOIN
 * KICK
 * QUIT
 **/

template<typename F, typename S>
bool asserEquals(F first, S second) {
	std::string green = "\033[32m";
	std::string end = "\033[0m";
	std::string red = "\033[31m";

	if (first == second)
		std::cout << std::endl << green + "TRUE" + end << std::endl;
	else
		std::cout << red + "FALSE" + end << std::endl;
	return (first == second);
}

int main() {
	std::string cmd1 = "NICK amy param1 param2 :message";
	//:Angel(от кого) PRIVMSG Wiz(кому) :Hello are you receiving this message ?
	CommandParser *parser = new CommandParser();
	Command *cmd = parser->parseCommand(cmd1);
	asserEquals(cmd->getName(), "NICK");

	asserEquals(cmd->getParams().at(0), "amy");
	asserEquals(cmd->getParams().at(1), "param1");
	asserEquals(cmd->getParams().at(2), "param2");
	asserEquals(cmd->getParams().size(), 3);
}