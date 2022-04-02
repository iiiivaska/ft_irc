//
// Created by Василий Буланов on 02.04.2022.
//

#include "Server.hpp"
#include "utils.hpp"

Server::Server(int argc, char **argv) {
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
void Server::accept_call() {
    _client_hint_size = sizeof(_client_hint);
    _client_socket = accept(_server_socket, (sockaddr*)&_client_hint, &_client_hint_size);

    if (_client_socket == -1) {
        std::cerr << "Problem with client connection!\n";
        exit(1);
    }
}

void Server::start() {

    set_server_socket();
    bind_socket();
    listen_socket();
    accept_call();

    //Close the listening socket
    close(_server_socket);

    memset(_host, 0, NI_MAXHOST);
    memset(_service, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&_client_hint, sizeof(_client_hint), _host, NI_MAXHOST, _service, NI_MAXSERV, 0);

    if ( result ) {
        std::cout << _host << " connected on " << _service << std::endl;
    } else {
        inet_ntop(AF_INET, &_client_hint.sin_addr, _host, NI_MAXHOST);
        std::cout << _host << " connected on " << ntohs(_client_hint.sin_port) << std::endl;
    }

    //While receiving - display message, echo message

    char buf[4096];
    while (true) {
        //Clear the buffer
        memset(buf, 0, BUFFER_SIZE);
        //Wait for a message
        int bytesRecv = recv(_client_socket, buf, BUFFER_SIZE, 0);
        std::cout << "Recieved bytes: " << bytesRecv << std::endl;
        if (bytesRecv == -1) {
            std::cerr << "There was a connection issue" << std::endl;
            break;
        }

        if  (bytesRecv == 0) {
            std::cout << "The client disconnected" << std::endl;
            break;
        }

        //Display message
        std::cout << "Recieved: " << std::string(buf, 0, bytesRecv);

        //Resend message
        int sd = send(_client_socket, buf, bytesRecv + 1, 0); //Возвращает количество отправленных байт, если отправил меньше нужного - необходимо дослать
        std::cout << "Sended bytes: " << sd << std::endl << std::endl;
    }

    //Close socket
    close(_client_socket);
}


Server::~Server() {

}