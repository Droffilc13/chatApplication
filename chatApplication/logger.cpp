#include "logger.h"
#include <ctime>
#include <iostream>

Logger::Logger(const std::string &filename) {
    logfile.open(filename, std::ios::app);
    if (!logfile.is_open()) {
        logfile.close();
        fprintf(stderr, "Unable to open log file: %s\n", filename.c_str());
    }
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

std::string Logger::getCurrentTime() const {
    std::time_t currentTime = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
    return std::string(buffer);
}

void Logger::logMessage(const std::string &message) {
    if (logfile.is_open()) {
        logfile << "[" << getCurrentTime() << "] " << message << std::endl;
        return;
    } else {
        fprintf(stderr, "Log file is not open.\n");
    }
}
