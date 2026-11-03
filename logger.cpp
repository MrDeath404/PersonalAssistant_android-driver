#include "logger.hpp"
#include <sstream>

Logger::Logger(const string& filename) {
    this->filename = filename;
}

Logger::~Logger() {
    if (file.is_open()) {
        file.close();
    }
}

string Logger::getTime(const string& format) {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm local_time = *localtime(&time);
    
    ostringstream oss;
    oss << put_time(&local_time, format.c_str());
    return oss.str();
}


void Logger::writeLog(const string& title, const string& message) {
    try {
        if (!file.is_open()) {
            file.open(filename, ios::app);
        }
        file << getTime("%Y-%m-%d-%H:%M:%S")
             << "[" << title << "] - "
             << message << endl;
    } catch (const exception& error) {
        throw runtime_error("Logger segment failed, you won't be able to see logs of this program. More information below:\n" + string(error.what()));
    }
}

void Logger::info(const string& message) {
    if (hasFlag(LOGGER_INFO)) {
        writeLog("INFO", message);
    }
}

void Logger::error(const string& message) {
    if (hasFlag(LOGGER_ERROR)) {
        writeLog("ERROR", message);
    }
}

void Logger::warning(const string& message) {
    if (hasFlag(LOGGER_WARNING)) {
        writeLog("WARNING", message);
    }
}

void Logger::clearLogs() {
    try {
        if (file.is_open()) {
            file.close();
        }
        file.open(filename, ios::out);
        file.close();
    } catch (const exception& error) {
        throw runtime_error("Logger segment failed, you won't be able to see logs of this program. More information below:\n" + string(error.what()));
    }
}

#ifdef LOGGER_GLOBAL
Logger logger("log.txt");
#endif