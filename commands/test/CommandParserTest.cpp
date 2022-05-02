#include "../includes/CommandParser.hpp"
#include <iostream>

/**
 * Example commands
 * NICK amy
 * WHOIS doctor
 * MODE amy +o
 * JOIN #tardis
 * PASS
 * USER
 * PRIVMSG
 * KICK
 * QUIT
 **/
//:Angel(от кого) PRIVMSG Wiz(кому) :Hello are you receiving this message ?

template<typename F, typename S>
bool assertEquals(const F &first, const S &second) {
	std::string green = "\033[32m";
	std::string end = "\033[0m";
	std::string red = "\033[31m";

	if (first == second)
		std::cout << green + "TRUE" + end << "(" << first << ", " << second << ")" << std::endl;
	else
		std::cout << red + "FALSE" + end << "(" << first << ", " << second << ")" << std::endl;
	return (first == second);
}

void successParseCommand1(int num) {

	std::cout << "TEST " << num << std::endl;
	std::string cmdStr = "NICK amy param1 param2 :message";
	CommandParser *parser = new CommandParser();
	Command *cmd = parser->parseCommand(cmdStr);

	assertEquals(cmd->getName(), "NICK");
	assertEquals(cmd->getParams().at(0), "amy");
	assertEquals(cmd->getParams().at(1), "param1");
	assertEquals(cmd->getParams().at(2), "param2");
	assertEquals(cmd->getCountParams(), 3);
	assertEquals(cmd->getMessage(), "message");
}

void successParseCommand2(int num) {
	std::cout << "TEST " << num << std::endl;

	std::string cmdStr = "PRIVMSG rory :Hey Rory...";
	CommandParser *parser = new CommandParser();
	Command *cmd = parser->parseCommand(cmdStr);

	assertEquals(cmd->getName(), "PRIVMSG");
	assertEquals(cmd->getParams().at(0), "rory");
	assertEquals(cmd->getCountParams(), 1);
	assertEquals(cmd->getMessage(), "Hey Rory...");
}

void successParseCommandBadSpacing(int num) {
	std::cout << "TEST " << num << std::endl;

	std::string cmdStr = "PRIVMSG rory         :      Hey Rory...       ";
	CommandParser *parser = new CommandParser();
	Command *cmd = parser->parseCommand(cmdStr);

	assertEquals(cmd->getName(), "PRIVMSG");
	assertEquals(cmd->getParams().at(0), "rory");
	assertEquals(cmd->getCountParams(), 1);
	assertEquals(cmd->getMessage(), "      Hey Rory...       ");
}

void failureParseNotFoundCommand(int num) {
	std::cout << "TEST " << num << std::endl;
	std::string cmdStr = "BADCMD rory         :      Hey Rory...       ";
	CommandParser *parser = new CommandParser();

	try {
		Command *cmd = parser->parseCommand(cmdStr);
	} catch (std::exception &ex) {
		assertEquals(std::string(ex.what()), "Not a command!");
	}
}

void successParseCommandWithMoreParamsAndMoreSpacing(int num) {
	std::cout << "TEST " << num << std::endl;
	std::string cmdStr = "       PRIVMSG        #cmsc23300      param1    param2         :          Hello everybody";
	CommandParser *parser = new CommandParser();
	Command *cmd = parser->parseCommand(cmdStr);

	assertEquals(cmd->getName(), "PRIVMSG");
	assertEquals(cmd->getParams().at(0), "#cmsc23300");
	assertEquals(cmd->getParams().at(1), "param1");
	assertEquals(cmd->getParams().at(2), "param2");
	assertEquals(cmd->getCountParams(), 3);
	assertEquals(cmd->getMessage(), "          Hello everybody");

}

void failureParseMoreParams(int num) {
	std::cout << "TEST " << num << std::endl;
	std::string cmdStr = "       PRIVMSG        #cmsc23300    "
						 "  p2  p3  p4 p5 p6 p7 p8 p9 p10  "
						 "  p11 p12 p13 p14  p15  p16"
						 "       : "
						 "         Hello everybody";
	CommandParser *parser = new CommandParser();
	try {
		Command *cmd = parser->parseCommand(cmdStr);
	} catch (std::exception &ex) {
		assertEquals(std::string(ex.what()), "Maximum params should be 15");
	}
}

void failureParseLongMessage(int num) {
	std::cout << "TEST " << num << std::endl;
	std::string cmdStr = "PRIVMSG  param1 param2:"
						 "asdasdadsasdasdasdasdasdasdasdasdasd1231231wee1231rf123131313123123123131311231233331123132123123132"
						 "asdasdadsasdasdasdasdasdasdasdasdasd1231231wee1231rf123131313123123123131311231233331123132123123132"
						 "asdasdadsasdasdasdasdasdasdasdasdasd1231231wee1231rf123131313123123123131311231233331123132123123132"
						 "asdasdadsasdasdasdasdasdasdasdasdasd1231231wee1231rf123131313123123123131311231233331123132123123132"
						 "asdasdadsasdasdasdasdasdasdasdasdasd1231231wee1231rf123131313123123123131311231233331123132123123132"
						 "1234567890123";
	CommandParser *parser = new CommandParser();
	try {
		Command *cmd = parser->parseCommand(cmdStr);
	} catch (std::exception &ex) {
		assertEquals(std::string(ex.what()), "Maximum message size should be 510");
	}
}

int main() {
	int testNumbers = 0;

	successParseCommand1(++testNumbers);
	successParseCommand2(++testNumbers);
	successParseCommandBadSpacing(++testNumbers);
	failureParseNotFoundCommand(++testNumbers);
	successParseCommandWithMoreParamsAndMoreSpacing(++testNumbers);
	failureParseMoreParams(++testNumbers);
	failureParseLongMessage(++testNumbers);
}