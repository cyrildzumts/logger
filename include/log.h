#ifndef LOG_H
#define LOG_H
#include "config.h"
#include "logger.h"

    #ifdef LOG_LEVEL_1

    static Loggin::Logger<LogFilePolicy> log_instance ("logger.log");

    #define LOG log_instance.print<Severity_Type::DEBUG>
    #define LOG_WARN log_instance.print<Severity_Type::WARNING>
    #define LOG_ERROR log_instance.print<Severity_Type::ERROR>

    #else
    static Loggin::Logger<LogConsolPolicy> log_instance ("Console Logger");
    #define LOG log_instance.print<Severity_Type::DEBUG>
    #define LOG_WARN log_instance.print<Severity_Type::WARNING>
    #define LOG_ERROR log_instance.print<Severity_Type::ERROR>

    #endif

#endif // LOG_H
