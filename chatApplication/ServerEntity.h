#ifndef SERVERENTITY_H
#define SERVERENTITY_H

#include "NetworkEntity.h"

// TODO: Clean this class up, this is not working
class ServerEntity : public NetworkEntity {
public:
    ServerEntity(const std::string &address = "127.0.0.1", const std::string &logFile = "server.log")
        : NetworkEntity(logFile), address(address) {}

    
    bool createSocket(const std::string &address);
    bool listenOnSocket();
    bool acceptClient();
private:
    std::string address;
    // SOCKET clientSocket;
};

#endif // SERVERENTITY_H