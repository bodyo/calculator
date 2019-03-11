include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += c++11
#CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

SOURCES += \
        main.cpp \
        ../token.cpp \
        ../shuntingyard.cpp \
    shuntingyardtest.cpp

HEADERS += \
        ../token.h \
        ../shuntingyard.h

