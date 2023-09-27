#include <iostream>

using namespace std;

enum class LogLevel {
    DEBUG,
    ERROR,
    WARNING,
    INFO,
    NONE
};

extern LogLevel minLogLevel; // The minimum log level to log

void log(LogLevel level, const string& message);
void setLogLevel(LogLevel level);