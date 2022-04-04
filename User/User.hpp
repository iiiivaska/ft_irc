#ifndef USER_HPP
# define USER_HPP
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
class User{
private:
    int                                 _fd;
    sockaddr_in                         _client_hint;
    std::string                         _hostname;
    int                                 _port;
    static std::map<int, User*>         users;
public:
    User(int fd, sockaddr_in client_hint);
    ~User();
    std::string         getHostname();
    int                 getPort();
    int                 getFd();
    static void         addUser(int fd, User *user);
    static User*        findUser(int fd);
    static int          deleteUser(int fd);
};

#endif