TARGET = CitrusHack2016
TEMPLATE = app
QT += core gui widgets
CONFIG += c++11

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    VirtualMachine.cpp \
    Keypad.cpp
HEADERS += \
    MainWindow.hpp \
    VirtualMachine.hpp \
    Keypad.hpp
FORMS += \
    MainWindow.ui
