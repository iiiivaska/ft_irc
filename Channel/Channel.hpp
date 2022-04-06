#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../Server/Server.hpp"
#include "../User/User.hpp"
class User;

class Channel {
private:
    static std::vector<Channel*> channels;
    std::vector<User> _users;
    std::string _name;
public:
    Channel(std::string name);
    ~Channel();
    void addUser(User user);
    void deleteUser(User user);
    static int addChannel(Channel *channel) {
        for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
            if ((*it.base())->getName() == channel->getName()) {
                return 1;
            }
        }
        Channel::channels.push_back(channel);
        return 0;
    };
    static int deleteChannel(Channel *channel){
        for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
            if ((*it.base())->getName() == channel->getName()) {
                Channel::channels.erase(it);
                return 0;
            }
        }
        return 1;
    };
    std::string getName();
    void setName(std::string name);
};

#endif