TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    logpolicy.cpp \
    logger.cpp

HEADERS += \
    logpolicy.h \
    logger.h \
    log.h
