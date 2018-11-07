#include <iostream>
//#define LOG_LEVEL_1
#include "log.h"

using namespace std;

int main()
{
    LOG("Starting Main Application");
    for(int i = 0; i < 5; i++){
        LOG("The value of 'i' is ", i, ". ", 3-i-1, " LOG REPORT");
    }
    LOG_WARN("class Logger not fully loaded");
    LOG_ERROR("PRECESSING ERROR");
    return 0;
}
