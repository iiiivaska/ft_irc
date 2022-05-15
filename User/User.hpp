#ifndef USER_HPP
# define USER_HPP
# define SUCCESS_AUTH 1
# define FAILURE_PASS 0
# define REGISTRED_USER 2
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <unistd.h>
#include "../Channel/Channel.hpp"

class Channel;

class User{
private:
    Channel*                            _channel;
    int                                 _fd;
    sockaddr_in                         _client_hint;
    std::string                         _hostname;
    int                                 _port;
    static std::map<int, User*>         users;
    int                                 _status;
    std::string                         _nick;
public:
    User(int fd, sockaddr_in client_hint);
    ~User();
    std::string         getHostname();
    int                 getPort();
    int                 getFd();
    static void         addUser(int fd, User *user);
    static User*        findUser(int fd);
	User*				findUserByNick(std::string name);
    static int          deleteUser(int fd);
    void                addChannel(Channel* channel);
    void                deleteChannel();
    int                 getStatus();
    void                setStatus(int status);
    Channel*            getChannel();
    std::string         getNick();
    void                setNick(std::string nick);
	bool				findUser(std::string nick);
};

#endif