#include "client.h"

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

int main(int argc, char *argv[]) {
    Logger clientLogger("client.txt");
    // Starting up winsock
    WSAData wsaData;
    int wsaerr;

    WORD version = MAKEWORD(2,2);
    wsaerr = WSAStartup(version, &wsaData);

    if (wsaerr != 0) {
        clientLogger.logMessage("Windows socket instantiation failed!");
        return 0;
    }

    // Create socket
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL; // This is used to traverse the addrinfo linkedlist
    struct addrinfo hints;
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        clientLogger.logMessage("getaddrinfo failed: " + iResult);
        WSACleanup();
        return 1;
    }

    SOCKET connectSocket = INVALID_SOCKET;

    ptr = result;
    connectSocket = socket(ptr->ai_family,
        ptr->ai_socktype,
        ptr->ai_protocol);

    if (connectSocket == INVALID_SOCKET) {
        clientLogger.logMessage("Error at socket: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to socket
    iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        clientLogger.logMessage("Unable to connect to server");
        WSACleanup();
        return 1;
    }

    // Sending and receiving data on the client
    int recvbuflen = DEFAULT_BUFLEN;
    char sendbuf[512] = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];

    // while (true) {
    //     std::string message;
    //     std::cout << "Enter your message: ";
    //     std::getline(std::cin, message);
        
    //     if (message.size() == 0 || message == "$quit") break;
    // }



    iResult = send(connectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        clientLogger.logMessage("Send failed: " + std::to_string(WSAGetLastError()));
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    clientLogger.logMessage("Bytes send: " + iResult);

    iResult = shutdown(connectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        clientLogger.logMessage("Shutdown failed: " + std::to_string(WSAGetLastError()));
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    do {
        iResult = recv(connectSocket, recvbuf, recvbuflen, 0);
        if (iResult == 0) {
            clientLogger.logMessage("Connection closed");
            continue;
        }

        if (iResult > 0) {
            clientLogger.logMessage("Bytes received: " + iResult);
        } else {
            clientLogger.logMessage("recv failed: " + std::to_string(WSAGetLastError()));
        }
    } while (iResult > 0);

    iResult = shutdown(connectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        clientLogger.logMessage("Shutdown failed: " + std::to_string(WSAGetLastError()));
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    closesocket(connectSocket);
    WSACleanup();

    return 0;
}