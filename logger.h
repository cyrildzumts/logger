#ifndef LOGGER_H
#define LOGGER_H
#include "logpolicy.h"
#include <fstream>
#include <sstream>
#include <mutex>

enum Severity_Type
{
   DEBUG = 1, ERROR,WARNING
};
namespace Loggin {


/**
 * This class provide logging facility.
 * Usage :
 * To write logs into a file then define the macro LOG_LEVEL_1 before including
 * "log.h"
 *
 * 0 - include "log.h" -- this define the Logger Macros
 * 1- DEBUG LOG :
 *      LOG("log report");
 *      or
 *      LOG("part of report", 2, "another part of the report");
 *
 * 2 - WARNING LOG :
 *      LOG_WARN("log report");
 *      or
 *      LOG_WARN("part of report", 2, "another part of the report");
 *
 * 3 - ERROR LOG :
 *      LOG_ERROR("log report");
 *      or
 *      LOG_ERROR("part of report", 2, "another part of the report");
 *
 *
 * Output examples :
 *  0000000 < Fri May 25 17:31:55 2018 - 0003118 >~ <DEBUG> :Starting Main Application
    0000001 < Fri May 25 17:31:55 2018 - 0003221 >~ <DEBUG> :The value of 'i' is 0. 2 LOG REPORT
    0000002 < Fri May 25 17:31:55 2018 - 0003271 >~ <DEBUG> :The value of 'i' is 1. 1 LOG REPORT
    0000003 < Fri May 25 17:31:55 2018 - 0003313 >~ <DEBUG> :The value of 'i' is 2. 0 LOG REPORT
    0000004 < Fri May 25 17:31:55 2018 - 0003346 >~ <DEBUG> :The value of 'i' is 3. -1 LOG REPORT
    0000005 < Fri May 25 17:31:55 2018 - 0003382 >~ <DEBUG> :The value of 'i' is 4. -2 LOG REPORT
    0000006 < Fri May 25 17:31:55 2018 - 0003412 >~ <WARNING> :class Logger not fully loaded
    0000007 < Fri May 25 17:31:55 2018 - 0003440 >~ <ERROR> :PRECESSING ERROR
 */


template<typename logpolicy>
class Logger
{
private:
    unsigned line_number;
    std::stringstream logstream;
    logpolicy *policy;
    std::mutex write_mutex;

private:
    std::string get_time();
    std::string get_line_header();

    void core_print();
    template<typename First, typename ...Rest>
    void core_print(First first, Rest...rest);

public:
    // WARING : the typename logpolicy must be default constructible
    Logger(const std::string &name);
    ~Logger();
    template<Severity_Type severity, typename ...Args>
    void print(Args...args);

};

template<typename logpolicy>
    template<Severity_Type severity, typename...Args>
void Logger<logpolicy>::print(Args ...args)
{
    write_mutex.lock();
    switch (severity) {
    case Severity_Type::DEBUG:
        logstream << "<DEBUG>   : ";
        break;
    case Severity_Type::WARNING:
        logstream << "<WARNING> : ";
        break;
    case Severity_Type::ERROR:
        logstream << "<ERROR>   : ";
        break;

    };
    core_print(args...);
    write_mutex.unlock();
}



template<typename logpolicy>
std::string Logger<logpolicy>::get_time()
{
    std::string time_str;
    time_t local_time;
    time(&local_time);
    time_str = ctime(&local_time);
    // return the time string without new line character
    return time_str.substr(0, time_str.size() - 1);
}

template<typename logpolicy>
std::string Logger<logpolicy>::get_line_header()
{
    std::stringstream header;
    header.str("");
    header.fill('0');
    header.width(7);
    header << line_number++ << " < " <<get_time() << " - ";
    header.fill('0');
    header.width(7);
    header << clock() << " >~ ";
    return  header.str();
}

template<typename logpolicy>
void Logger<logpolicy>::core_print()
{
    policy->write_stream(get_line_header() + logstream.str());
    logstream.str("");
}


template<typename logpolicy>
Logger<logpolicy>::Logger(const std::string &name)
{
    line_number = 0;
    policy = new logpolicy;
    if(!policy){
        throw std::runtime_error("LOGGER: Unable to create a logger instance");
    }
    policy->open_stream(name);
}

template<typename logpolicy>
Logger<logpolicy>::~Logger()
{
    if(policy){
        policy->close_stream();
        delete policy;
    }

}

template<typename logpolicy>
    template<typename First, typename...Rest>
void Logger<logpolicy>::core_print(First first, Rest...rest)
{
    logstream << first;
    core_print(rest...);
}

}
#endif // LOGGER_H
