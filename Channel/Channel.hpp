#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../Server/Server.hpp"
#include "../User/User.hpp"
class User;

class Channel {
private:
    std::vector<User> _users;
    std::string _name;
public:
    Channel(std::string name);
    ~Channel();
    void addUser(User user);
    void deleteUser(User user);
    std::string getName();
    void setName(std::string name);
    std::vector<User> getUsers();
};

#endif