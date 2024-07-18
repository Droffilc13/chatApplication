// chatApplication.cpp : Defines the entry point for the application.
//

#include "chatApplication.h"
#include "Logger.h"

using namespace std;

int main() {
    std::cout << "Hello world" << std::endl;
	Logger logger("testlog.txt");
    

    logger.logMessage("Application started");
    logger.logMessage("This is a test log message");
    logger.logMessage("Application ended");
	return 0;
}
