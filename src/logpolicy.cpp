#include "logpolicy.h"

LogPolicy::~LogPolicy()
{

}

LogFilePolicy::LogFilePolicy() : outputstream{new std::ofstream}
{

}

LogFilePolicy::~LogFilePolicy()
{
    if(outputstream)
        outputstream->close();
}

void LogFilePolicy::open_stream(const std::string &filename)
{
    outputstream->open(filename.c_str(),std::ios_base::binary|std::ios_base::out);
    if(!outputstream->is_open()){
        throw(std::runtime_error("LOGGER : Unable to open an output stream"));
    }
}

void LogFilePolicy::close_stream()
{
    if(outputstream)
        outputstream->close();
}

void LogFilePolicy::write_stream(const std::string &report)
{
    (*outputstream) << report << std::endl;
}

/****************************************************************/
LogConsolPolicy::LogConsolPolicy()
{

}

LogConsolPolicy::~LogConsolPolicy()
{

}

void LogConsolPolicy::open_stream(const std::string &filename)
{
    std::cout << __PRETTY_FUNCTION__ << " opening " << filename << std::endl;
}

void LogConsolPolicy::close_stream()
{

}

void LogConsolPolicy::write_stream(const std::string &report)
{
    std::cout << report << std::endl;
}

