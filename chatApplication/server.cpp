#include "server.h"
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

int main() {
    Logger serverLogger("server.txt");
    WSAData wsaData;
    int wsaerr;

    WORD version = MAKEWORD(2,2);
    wsaerr = WSAStartup(version, &wsaData);

    if (wsaerr != 0) {
        serverLogger.logMessage("Windows socket instantiation failed!");
        return 0;
    }

    // Create Socket
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    
    if (iResult != 0) {
        serverLogger.logMessage("getaddrinfo failed");
        WSACleanup();
        return 1;
    }

    SOCKET listenSocket = INVALID_SOCKET;

    listenSocket = socket(result->ai_family,
        result->ai_socktype,
        result->ai_protocol);

    if (listenSocket == INVALID_SOCKET) {
        serverLogger.logMessage("Error creating socket");
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Bind socket to port
    iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        serverLogger.logMessage("Bind failed");
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // Listening on a socket (Where is this)
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        serverLogger.logMessage("Listening to port failed");
        closesocket(listenSocket);
        WSACleanup();
    }

    // Accepting a socket
    SOCKET clientSocket = INVALID_SOCKET;

    clientSocket = accept(listenSocket, NULL, NULL);

    if (clientSocket == INVALID_SOCKET) {
        serverLogger.logMessage("Accept failed");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    
    // Receiving and send message
    char recvbuf[DEFAULT_BUFLEN];
    int iSendResult;
    int recvbuflen = DEFAULT_BUFLEN;

    do {
        iResult = recv(clientSocket, recvbuf, recvbuflen, 0);

        if (iResult == 0) {
            serverLogger.logMessage("Connection closing");
            continue;
        }

        if (iResult > 0) {
            serverLogger.logMessage("Bytes received: ");

            iSendResult = send(clientSocket, recvbuf, iResult, 0);

            if (iSendResult == SOCKET_ERROR) {
                serverLogger.logMessage("Send failed");
                closesocket(clientSocket);
                WSACleanup();
                return 1;
            }

            serverLogger.logMessage("Bytes sent");
            /* print out message to console */
            // recvbuf[iResult] = '\0';
            std::cout << "Server receives: " << recvbuf << std::endl;
            /*                             */ 
        } else {
            serverLogger.logMessage("Recv failed");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    iResult = shutdown(clientSocket, SD_SEND);

    if (iResult == SOCKET_ERROR) {
        serverLogger.logMessage("Shutdown failed");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}