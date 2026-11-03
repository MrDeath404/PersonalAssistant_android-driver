#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

#define LOGGER_DISABLED 0
#define LOGGER_INFO 2
#define LOGGER_ERROR 4
#define LOGGER_WARNING 8
#define LOGGER_ENABLED (LOGGER_INFO | LOGGER_ERROR | LOGGER_WARNING)

//#define LOGGER_DEBUG
#define LOGGER_GLOBAL

using namespace std;

class Logger {
#ifndef LOGGER_DEBUG
private:
#else
public:
#endif
    fstream file;
    string filename;
    int flags = LOGGER_ENABLED;
    string getTime(const string& format);
    void writeLog(const string& title, const string& message);
public:
    Logger() {/* None here */};
    Logger(const string& filename);
    ~Logger();
    void setFileName(const string& filename) { this->filename = filename; };
    bool hasFlag(int flag) { return flags & flag; }
    void removeFlag(int flag) { flags &= ~(flag); }
    void addFlag(int flag) { flags |= flag; }
    void setFlags(int flags) { this->flags = flags; }
    void info(const string& message);
    void error(const string& message);
    void warning(const string& message);
    void clearLogs();
};

#ifdef LOGGER_GLOBAL
extern Logger logger;
#endif