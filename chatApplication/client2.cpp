#include "ClientEntity.h"

int main() {

    ClientEntity client("localhost", "client.log");
    client.initializeWinsock();

    if(!client.connectToServer()) {
        return 1;
    }

    std::string message = "this is a test";

    if (!client.sendData(message)) {
        return 1;
    }

    client.receiveData();

    return 0;
}