#include "NetworkEntity.h"


bool NetworkEntity::initializeWinsock() {
    WORD version = MAKEWORD(2, 2);
    iResult = WSAStartup(version, &wsaData);
    if (iResult != 0) {
        logger.logMessage("WSAStartup failed: " + std::to_string(iResult));
        return false;
    }
    return true;
}


bool NetworkEntity::createSocket(const std::string &address) {
    // Basic info 
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(address.c_str(), DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        logger.logMessage("getaddrinfo failed: " + iResult);
        WSACleanup();
        return false;
    }

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

    std::cout << std::to_string(connectSocket) << std::endl;

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

    return true;

}

bool NetworkEntity::receiveData() {
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];

    do {
        iResult = recv(connectSocket, recvbuf, recvbuflen, 0);
        if (iResult == 0) {
            logger.logMessage("Connection closed");
            continue;
        }

        if (iResult > 0) {
            logger.logMessage("Bytes received: " + iResult);
        } else {
            logger.logMessage("recv failed: " + std::to_string(WSAGetLastError()));
            return false;
        }
    } while (iResult > 0);

    return true;
}