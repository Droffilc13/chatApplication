#include "ServerEntity.h"

bool ServerEntity::createSocket(const std::string &address) {
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        logger.logMessage("getaddrinfo failed: " + iResult);
        WSACleanup();
        return false;
    }

    connectSocket = socket(result->ai_family,
        result->ai_socktype,
        result->ai_protocol);

    if (connectSocket == INVALID_SOCKET) {
        logger.logMessage("Error at socket: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);   
        WSACleanup();
        return false;
    }

    return true;
}

bool ServerEntity::listenOnSocket() {
    if (listen(connectSocket, SOMAXCONN) == SOCKET_ERROR) {
        logger.logMessage("Listening to port failed");
        closesocket(connectSocket);
        WSACleanup();
        return false;
    }

    return true;
}

bool ServerEntity::acceptClient() {
    clientSocket = accept(connectSocket, NULL, NULL);

    if (clientSocket == INVALID_SOCKET) {
        logger.logMessage("Acceptance of client connection failed");
        closesocket(connectSocket);
        WSACleanup();
        return false;
    }

    return true;
}
