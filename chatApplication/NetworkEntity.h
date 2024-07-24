#ifndef NETWORKENTITY_H
#define NETWORKENTITY_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "logger.h"  // Assuming logger.h is your logger class header

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

class NetworkEntity {
public:
    NetworkEntity(std::string logFilePath):
        logger(Logger(logFilePath)), connectSocket(INVALID_SOCKET),
        clientSocket(INVALID_SOCKET), result(NULL), ptr(NULL) {}

    /*
     * bool returns whether operation is successful
     */
    bool initializeWinsock();

    bool createSocket(const std::string &address);

    bool bindSocket();

    bool sendData(const std::string message);

    bool receiveData();

    // void cleanup();

    //bool 

    // virtual ~NetworkEntity() {
    //     cleanup();
    // }

    // TODO: Create socket, connect socket, accept message, send message, shutdown, cleanup
protected:
    Logger logger;
    SOCKET connectSocket;
    SOCKET clientSocket;

    // ptr moves through the addrinfo linked list, result points at the same head
    struct addrinfo *result;
    struct addrinfo *ptr;
    struct addrinfo hints;

    // Stores error code of latest call to winsock2 library functions
    int iResult;

    WSAData wsaData;
};

#endif //NETWORKENTITY_H