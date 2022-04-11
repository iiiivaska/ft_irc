#include "Server/Server.hpp"

int main(int argc, char** argv) {

    Server server = Server(argc, argv);
    server.start();
}

