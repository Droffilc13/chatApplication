#include "ServerEntity.h"

int main() {
    ServerEntity server("localhost", "server.log");

    if (!server.initializeWinsock()) return 1;
    std::cout << "initialise winsock" << std::endl;
    if (!server.createSocket("")) return 1;
    std::cout << "create socket" << std::endl;
    if (!server.bindSocket()) return 1;
    std::cout << "bind socket" << std::endl;
    if (!server.listenOnSocket()) return 1;
    std::cout << "listen on socket" << std::endl;

    if (!server.acceptClient()) return 1;
    std::cout << "accept client" << std::endl;
    if (!server.receiveData()) return 1;
    std::cout << "DONE" << std::endl;

    // if (!server.sendData("Message received successful!")) return 1;

    return 0;
}