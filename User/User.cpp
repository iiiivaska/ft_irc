#include "User.hpp"

std::map<int, User*> User::users = std::map<int, User*>();

User::User(int fd, sockaddr_in client_hint) {
    _fd = fd;
    _client_hint = client_hint;
    _hostname = inet_ntoa(_client_hint.sin_addr);
    _port = ntohs(_client_hint.sin_port);
}

User::~User() {

}

std::string User::getHostname() {
    return _hostname;
}

int User::getPort() {
    return _port;
}

int User::getFd() {
    return _fd;
}

void User::addUser(int fd, User *user) {
    users.insert(std::make_pair(fd, user));
}

User* User::findUser(int fd) {
    return users.find(fd)->second;
}

//return 1: такого пользователя нет, return 0: все успешно
int User::deleteUser(int fd) {
    for(std::map<int, User*>::iterator item = users.begin(); item != users.end(); ++item)
    {
        std::cout << item->first << " : " << item->second << std::endl; //Вывод ключей и значений
    }
    //write(1, "a", 1);
    User *user = findUser(fd);
    std::cout<<"User: " << user->getHostname() << " with port " << user->getPort() << " deleted\n";
    delete user;
    return users.erase(fd) == 0 ? 1 : 0;
}

//std::vector<pollfd>::iterator User::getClientPollFd() {
//    return _client_poll_fd;
//}

