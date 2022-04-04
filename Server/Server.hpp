#ifndef SERVER_HPP
# define SERVER_HPP

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
#include "../User/User.hpp"
#define BUFFER_SIZE 4096

class Server {
    struct args {
        std::string password;
        int port;
    };


public:
    Server(int argc, char **argv);
    ~Server();

    void            start();

private:
    int                 _working;
    int                 _port;
    std::string         _password;
    int                 _server_socket;
    sockaddr_in         _hints;
//    sockaddr_in         _client_hint;
//    socklen_t           _client_hint_size;
//    int                 _client_socket;
//    char                _host[NI_MAXHOST];
//    char                _service[NI_MAXSERV];
    pollfd              _server_fd;
    std::vector<pollfd> _poll_fds;
    void                parse_args(int argc, char** argv);
    void                check_port_before_parse(char *str);
    void                set_server_socket();
    void                bind_socket();
    void                listen_socket();
    void                accept_call();
    void                disconnect_user(int fd);
    std::vector<pollfd>::iterator   find_fd(int fd);
    void                message(int fd);
    void                readMessage(int fd);
};

#endif
