#include "Channel.hpp"

std::vector<Channel*> channels = std::vector<Channel*>();

Channel::Channel(std::string name) {
    _name = name;
}

Channel::~Channel() {

}

std::string Channel::getName() {
    return _name;
}

void Channel::setName(std::string name) {
    _name = name;
}

void Channel::addUser(User user) {
    for (std::vector<User>::iterator it = _users.begin(); it != _users.end(); it++) {
        if (it->getFd() == user.getFd()) {
            return ;
        }
    }
    _users.push_back(user);
}

void Channel::deleteUser(User user) {
    for (std::vector<User>::iterator it = _users.begin(); it != _users.end(); it++) {
        if (it->getFd() == user.getFd()) {
            _users.erase(it);
            return ;
        }
    }
}



//int Channel::addChannel(Channel *channel) {
//    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
//        if ((*it.base())->getName() == channel->getName()) {
//            return 1;
//        }
//    }
//    Channel::channels.push_back(channel);
//    return 0;
//}

//int Channel::deleteChannel(Channel *channel) {
//    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
//        if ((*it.base())->getName() == channel->getName()) {
//            Channel::channels.erase(it);
//            return 0;
//        }
//    }
//    return 1;
//}