#include "log.h"
using namespace std;

LogLevel minLogLevel = LogLevel::INFO; 

void log(LogLevel level, const string& message) {

    if (level < minLogLevel) {
        return; // If the log level is lower than the minimum, don't log the message
    }

    string colorCode;
    string levelString;

    switch (level) {
        case LogLevel::INFO:
            colorCode = "\033[32m"; // Green
            levelString = "INFO";
            break;
        case LogLevel::WARNING:
            colorCode = "\033[33m"; // Yellow
            levelString = "WARNING";
            break;
        case LogLevel::ERROR:
            colorCode = "\033[31m"; // Red
            levelString = "ERROR";
            break;
        case LogLevel::DEBUG:
            colorCode = "\033[36m"; // Cyan
            levelString = "DEBUG";
            break;

    }

    cout << colorCode << "[" << levelString << "] " << message << "\033[0m" << endl;
}

void setLogLevel(LogLevel level) {
    minLogLevel = level;
}