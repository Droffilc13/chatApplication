#include "ClientEntity.h"

int main() {

    ClientEntity client("localhost", "client.log");
    
    if (!client.initializeWinsock()) return 1;
    std::cout << "Initialise winsock" << std::endl;
    if (!client.connectToServer()) return 1;
    std::cout << "Connected to server" << std::endl;

    std::string message = "Hey Server! Can you hear me?";
    if (!client.sendData(message)) return 1;
    std::cout << "Data sent" << std::endl;
    // if (!client.receiveData()) return 1;
    // std::cout << "received data" << std::endl;

    return 0;
}