#include "NetworkEntity.h"
// TODO: Clean this class up, this is not working
class Client : public NetworkEntity {
public:
    Client(const std::string &address = "127.0.0.1", const std::string &logFile = "client.txt")
        : NetworkEntity(logFile), address(address) {}

    bool connectToServer() {
        if (!createSocket(address)) {
            return false;
        }

        int iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            freeaddrinfo(ptr);
            WSACleanup();
            logger.logMessage("Unable to connect to server");
            return false;
        }

        freeaddrinfo(ptr);
        return true;
    }

private:
    std::string address;
};
