#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>

#define BUFFER_SIZE 4096

struct args {
    std::string password;
    int port;
};

int ft_atoi(char* s)
{
    int n = 0;
    while( *s >= '0' && *s <= '9' ) {
        n *= 10;
        n += *s++;
        n -= '0';
    }
    return n;
}

void check_port_before_parse(char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') {
            std::cerr << "Incorrect port, only numbers allowed!\n";
            exit(1);
        }
        str++;
    }
}

void parse_args(args* arguments, int argc, char** argv) {
    if (argc <= 1 || argc >=4) {
        std::cerr << "ERROR: Bad arguments!\n";
        std::cerr << "Please pass port as first argument, and password as second: ./ircserv <port> <password>\n";
        exit(1);
    }
    check_port_before_parse(argv[1]);
    if (argc > 1) {
        arguments->port = ft_atoi(argv[1]);
        if (arguments->port < 1024 || arguments->port > 65535) {
            std::cerr << "Bad port argument, correct port between 1024 and 65535.\n";
            exit(1);
        }
        if (argc > 2) {
            arguments->password = argv[2];
        }
    }
}

int main(int argc, char** argv) {

    //Parse port and password
    args *arguments = new args;
    parse_args(arguments, argc, argv);

    //Create socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    if (listening == -1) {
        std::cerr << "Can`t create a socket!";
        exit(1);
    }

    //Bind the socket to an IP / port
    sockaddr_in hint;

    hint.sin_family = AF_INET;
    hint.sin_port = htons(arguments->port);
    hint.sin_addr.s_addr = inet_addr("0.0.0.0");
    //inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); //МБ нельзя юзать


    //Make socket reusable instantly
    int yes = 1;
    if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "ERROR: setsockopt!\n";
        exit(1);
    }

    //Continue Binding
    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
        std::cerr << "Can`t bind to IP/port!.\n";
        std::cerr << std::strerror(errno);
        exit(1);
    }

    //Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1) {
        std::cerr << "Can`t listen";
        exit(1);
    }

    //Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    if (clientSocket == -1) {
        std::cerr << "Problem with client connection!";
        exit(1);
    }

    //Close the listening socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if ( result ) {
        std::cout << host << " connected on " << svc << std::endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;
    }

    //While receiving - display message, echo message

    char buf[4096];
    while (true) {
        //Clear the buffer
        memset(buf, 0, BUFFER_SIZE);
        //Wait for a message
        int bytesRecv = recv(clientSocket, buf, BUFFER_SIZE, 0);
        if (bytesRecv == -1) {
            std::cerr << "There was a connection issue" << std::endl;
            break;
        }

        if  (bytesRecv == 0) {
            std::cout << "The client disconnected" << std::endl;
            break;
        }

        //Display message
        std::cout << "Recieved: " << std::string(buf, 0, bytesRecv) << std::endl;

        //Resend message
        send(clientSocket, buf, bytesRecv + 1, 0);
    }

    //Close socket
    close(clientSocket);
}

