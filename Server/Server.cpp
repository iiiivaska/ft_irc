//
// Created by Василий Буланов on 02.04.2022.
//

#include "Server.hpp"
#include "../utils.hpp"


Server::Server(int argc, char **argv) {
    _working = 0;
    parse_args(argc, argv);
}

//Парсим и проверяем подаваемые аргументы
void Server::parse_args(int argc, char **argv) {
    if (argc <= 1 || argc >=4) {
        std::cerr << "ERROR: Bad arguments!\n";
        std::cerr << "Please pass port as first argument, and password as second: ./ircserv <port> <password>\n";
        exit(1);
    }
    check_port_before_parse(argv[1]);
    if (argc > 1) {
        _port = ft_atoi(argv[1]);
        if (_port < 1024 || _port > 65535) {
            std::cerr << "Bad port argument, correct port between 1024 and 65535.\n";
            exit(1);
        }
        if (argc > 2) {
            _password = argv[2];
        }
    }
}
void Server::check_port_before_parse(char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') {
            std::cerr << "Incorrect port, only numbers allowed!\n";
            exit(1);
        }
        str++;
    }
}
//---------------------------------------

//Создаем сокет сервера
void Server::set_server_socket() {
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_server_socket == -1) {
        std::cerr << "Can`t create a socket!.\n";
        exit(1);
    }
}

//Bind the socket to an IP / port
void Server::bind_socket() {
    _hints.sin_family = AF_INET;
    _hints.sin_port = htons(_port);
    _hints.sin_addr.s_addr = inet_addr("0.0.0.0");


    //Make socket reusable instantly
    int yes = 1;
    if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "ERROR: setsockopt!.\n";
        std::cerr << std::strerror(errno);
        exit(1);
    }

    //Делаем сокет неблокирующим
    if (fcntl(_server_socket, F_SETFL, O_NONBLOCK) == -1) {
        std::cerr << "ERROR: while setting socket to NON-BLOCKING!.\n";
        exit(1);
    }

    //Continue Binding
    if (bind(_server_socket, (sockaddr*)&_hints, sizeof(_hints)) == -1) {
        std::cerr << "Can`t bind to IP/port!.\n";
        std::cerr << std::strerror(errno);
        exit(1);
    }
}

//Mark the socket for listening in
void Server::listen_socket() {
    if (listen(_server_socket, SOMAXCONN) == -1) {
        std::cerr << "Can`t listen.\n";
        std::cerr << std::strerror(errno);
        exit(1);
    }
}

//Accept a call
//void Server::accept_call() {
//    _client_hint_size = sizeof(_client_hint);
//    _client_socket = accept(_server_socket, (sockaddr*)&_client_hint, &_client_hint_size);
//
//    if (_client_socket == -1) {
//        std::cerr << "Problem with client connection!\n";
//        exit(1);
//    }
//}

void Server::accept_call() {
    int _client_fd;
    sockaddr_in _client_hint;
    socklen_t _client_hint_size = sizeof(_client_hint);

    _client_fd = accept(_server_socket, (sockaddr*)&_client_hint, &_client_hint_size);
    if (_client_fd < 0) {
        std::cerr << "Problem with client connection!\n";
        exit(1);
    }

    pollfd client_poll_fd;
    client_poll_fd.fd = _client_fd;
    client_poll_fd.events = POLLIN;
    client_poll_fd.revents = 0;



    _poll_fds.push_back(client_poll_fd);

    //Необходимо сохранить клиента в мапу
    User *user = new User(_client_fd, _client_hint);
    User::addUser(user->getFd(), user);

    std::cout << "Client: " << User::findUser(_client_fd)->getHostname() << " connected with port: "<< User::findUser(_client_fd)->getPort() << std::endl;
}

std::vector<pollfd>::iterator Server::find_fd(int fd) {
    for (std::vector<pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); it++) {
        if (it.base()->fd == fd) {
            return it;
        }
    }
    return _poll_fds.begin();
}

void Server::disconnect_user(int fd) {
    std::cout<<"Deleting: "<<fd<<std::endl;
    for (std::vector<pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); it++) {
        std::cout << it.base()->fd << " | ";
    }
    std::cout << std::endl;
    User *user = User::findUser(fd);
    std::vector<pollfd>::iterator fd_iter = find_fd(user->getFd());
    if (fd_iter == _poll_fds.begin()) {
        std::cout << "Error while deleting user, no such fd\n";
        return;
    }
    _poll_fds.erase(fd_iter);
    if (user->getChannel() != nullptr) {
        user->getChannel()->deleteUser(user);
    }
    if (User::deleteUser(fd)) {
        std::cout << "Error: user was not disconnected\n";
        return;
    }
}

void Server::message(int fd) {
    std::string message;
    char buffer[BUFFER_SIZE];

    bzero(buffer, BUFFER_SIZE);

    //Получаем сообщение
    User *user = User::findUser(fd);
    if (recv(fd, buffer, BUFFER_SIZE, 0) < 0) {
        std::cerr << "Error while reading message\n";
        exit(1);
    }
    message.append(buffer);
    std::cout << "Message: " << message << " " << user->getHostname() << "\n";
    CommandParser parser = CommandParser();
    Command *command = parser.parseCommand(message);
    std::cout << "getName(): " << command->getName() << "\n" << "getMessage(): " << command->getMessage() << std::endl;
    if (user->getStatus() == 0) {
        //Залогинить пользователя
    } else {
        //Обработать команду
    }
//    //Test
//    if(strstr(message.c_str(), "ADDCHANNEL")) {
//        if (addChannel(new Channel("mow\n")) == 1) {
//            std::cout << "ERROR: Channel exist\n";
//            return;
//        }
//        std::cout << "Channel Added\n";
//        return;
//    }
//    //std::cout << message.substr(0, message.find(" ")) << "\n";
//    if(strstr(message.substr(0, message.find(" ")).c_str(), "ADDTO")) {
//        std::cout << message.substr(6, message.find(" ")) << "\n";
//        Channel* channel = findChannel(message.substr(6, message.find(" ")));
//        if (channel) {
//            user->addChannel(channel);
//            channel->addUser(user);
//            std::cout << user->getPort() << " added to channel " << channel->getName() << std::endl;
//        } else {
//            std::cout << "No such channel " << "\n";
//        }
//        return ;
//    }
//    if (user->getChannel() == nullptr) {
//        std::cout<<"Send to all\n";
//        for (std::vector<pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); it++) {
//            User *usr = User::findUser(it->fd);
//            if (usr != nullptr) {
//                if (it->fd != fd && usr->getChannel() == nullptr) {
//                    send(it->fd, buffer, sizeof(message) + 1, 0);
//                }
//            }
//        }
//    } else {
//        std::cout<<"Send to " << user->getChannel()->getName() << std::endl;
//        std::vector<User*> users = user->getChannel()->getUsers();
//        for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++) {
//            if ((*it)->getFd() != fd) {
//                send((*it)->getFd(), buffer, sizeof(message) + 1, 0);
//            }
//        }
//    }
//    //EndTest
}

void Server::start() {
    _working = 1;
    set_server_socket();
    bind_socket();
    listen_socket();
    //accept_call();

    _server_fd.fd = _server_socket;
    _server_fd.events = POLLIN;
    _server_fd.revents = 0;

    _poll_fds.push_back(_server_fd);

    _users = 0;
    while (_working) {
        if (_users == 5) {
            _working = 0;
        }
        if (poll(_poll_fds.begin().base(), _poll_fds.size(), -1) < 0) {
            std::cerr << "Error: while polling fds\n";
            exit(1);
        }

        for (std::vector<pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); it++) {
            if (it->revents == 0) {
                continue;
            }

            //Клиент отключился
            if ((it->revents & POLLHUP) == POLLHUP) {
                disconnect_user(it->fd);
                break ;
            }

            if ((it->revents & POLLIN) == POLLIN) {
                //клиент подключился
                if (it->fd == _server_socket) {
                    _users++; //временно
                    accept_call();
                    break ;
                }

                //Сообщение
                message(it->fd);
            }

        }
    }

//    //Close the listening socket
//    close(_server_socket);
//
//    memset(_host, 0, NI_MAXHOST);
//    memset(_service, 0, NI_MAXSERV);
//
//    int result = getnameinfo((sockaddr*)&_client_hint, sizeof(_client_hint), _host, NI_MAXHOST, _service, NI_MAXSERV, 0);
//
//    if ( result ) {
//        std::cout << _host << " connected on " << _service << std::endl;
//    } else {
//        inet_ntop(AF_INET, &_client_hint.sin_addr, _host, NI_MAXHOST);
//        std::cout << _host << " connected on " << ntohs(_client_hint.sin_port) << std::endl;
//    }
//
//    //While receiving - display message, echo message
//
//    char buf[BUFFER_SIZE];
//    while (true) {
//        //Clear the buffer
//        memset(buf, 0, BUFFER_SIZE);
//        //Wait for a message
//        int bytesRecv = recv(_client_socket, buf, BUFFER_SIZE, 0);
//        std::cout << "Recieved bytes: " << bytesRecv << std::endl;
//        if (bytesRecv == -1) {
//            std::cerr << "There was a connection issue" << std::endl;
//            break;
//        }
//
//        if  (bytesRecv == 0) {
//            std::cout << "The client disconnected" << std::endl;
//            break;
//        }
//
//        //Display message
//        std::cout << "Recieved: " << std::string(buf, 0, bytesRecv);
//
//        //Resend message
//        int sd = send(_client_socket, buf, bytesRecv + 1, 0); //Возвращает количество отправленных байт, если отправил меньше нужного - необходимо дослать
//        std::cout << "Sended bytes: " << sd << std::endl << std::endl;
//    }
//
//    //Close socket
//    close(_client_socket);
}

int Server::addChannel(Channel *channel) {
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if ((*it.base())->getName() == channel->getName()) {
            return 1;
        }
    }
    channels.push_back(channel);
    return 0;
};

int Server::deleteChannel(Channel *channel) {
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if ((*it.base())->getName() == channel->getName()) {
            channels.erase(it);
            return 0;
        }
    }
    return 1;
};

Channel *Server::findChannel(std::string name) {
    for(std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if ((*it.base())->getName() == name) {
            return (*it.base());
        }
    }
    return nullptr;
};

Server::~Server() {

}