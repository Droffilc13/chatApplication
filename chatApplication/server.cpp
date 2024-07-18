#include "server.h"

int main() {
    Logger
    WSAData wsaData;
    int wsaerr;

    WORD version = MAKEWORD(2,2);
    wsaerr = WSAStartup(version, &wsaData);

    if (wsaerr != 0) {
        
        return 0;
    }
}
