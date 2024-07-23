#include "NetworkEntity.h"

bool NetworkEntity::createSocket() {
    // Basic info 
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        logger.logMessage("getaddrinfo failed: " + iResult);
        WSACleanup();
        return false;
    }

    SOCKET connectSocket = INVALID_SOCKET;

    ptr = result;
    connectSocket = socket(ptr->ai_family,
        ptr->ai_socktype,
        ptr->ai_protocol);

    if (connectSocket == INVALID_SOCKET) {
        logger.logMessage("Error at socket: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    return true;
}

bool NetworkEntity::bindSocket() {
    iResult = bind(connectSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        logger.logMessage("Bind failed");
        freeaddrinfo(result);
        closesocket(connectSocket);
        WSACleanup();
        return false;
    }

    freeaddrinfo(result);
    return true;
}

bool NetworkEntity::sendData(const std::string message) {
    iResult = send(connectSocket, message.c_str(), (int)message.length(), 0);
    if (iResult == SOCKET_ERROR) {
        logger.logMessage("Send failed: " + std::to_string(WSAGetLastError()));
        closesocket(connectSocket);
        WSACleanup();
        return false;
    }
    // TODO
    if () {

    } else {

    }

    return true;

}

bool NetworkEntity::receiveData(std::string &receivedData) {
    //TODO
    iResult = recv(connectSocket, )
}