#include "ClientEntity.h"
#include "assert.h"

bool ClientEntity::connectToServer() {
    if (!createSocket(address)) {
        return false;
    }

    std::cout << std::to_string(connectSocket) << std::endl;

    int iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
        freeaddrinfo(ptr);
        WSACleanup();
        logger.logMessage("Unable to connect to server: ");
        printf("%d\n", WSAGetLastError());
        return false;
    }

    freeaddrinfo(ptr);
    return true;
}