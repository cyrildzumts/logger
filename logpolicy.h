#ifndef LOGPOLICY_H
#define LOGPOLICY_H
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
/**
 * @brief The LogPolicy class This class describe the type
 * of logging to use.
 */
class LogPolicy
{
public:
    virtual ~LogPolicy();
    virtual void open_stream(const std::string &filename)=0;
    virtual void close_stream()=0;
    virtual void write_stream(const std::string &report)=0;
};


/**
 * @brief The LogFilePolicy class
 * This class implements Loggin to File policy.
 */
class LogFilePolicy : public LogPolicy{
private:
    std::unique_ptr<std::ofstream> outputstream;

public:



    // LogPolicy interface
public:
    LogFilePolicy();
    ~LogFilePolicy();
    virtual void open_stream(const std::string &filename);
    virtual void close_stream();
    virtual void write_stream(const std::string &report);
};


class LogConsolPolicy : public LogPolicy{

public:



    // LogPolicy interface
public:
    LogConsolPolicy();
    ~LogConsolPolicy();
    virtual void open_stream(const std::string &filename);
    virtual void close_stream();
    virtual void write_stream(const std::string &report);
};

#endif // LOGPOLICY_H
