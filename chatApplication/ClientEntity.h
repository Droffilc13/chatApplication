#include "NetworkEntity.h"
// TODO: Clean this class up, this is not working
class ClientEntity : public NetworkEntity {
public:
    ClientEntity(const std::string &address = "127.0.0.1", const std::string &logFile = "client.log")
        : NetworkEntity(logFile), address(address) {}

    bool connectToServer();
private:
    std::string address;
};
