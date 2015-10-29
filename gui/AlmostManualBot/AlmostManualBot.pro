#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T03:18:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlmostManualBot
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

INCLUDEPATH += ../../src

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/TibiaFinder.cpp \
    ../../src/HealerRulesTable.cpp \
    ../../src/utils.cpp \
    ../../src/ConfigFromUiGenerator.cpp \
    ../../src/Bot.cpp \
    ../../src/Addresses.cpp \
    ../../src/BotCore.cpp \
    ../../src/Healer.cpp \
    ../../src/HealRule.cpp \
    ../../src/Module.cpp \
    ../../src/ModulesManager.cpp \
    ../../src/Simulator.cpp \
    ../../src/TibiaStuffReader.cpp

HEADERS  += mainwindow.h \
    ../../src/utils.hpp \
    ../../src/TibiaStuffReader.hpp \
    ../../src/Simulator.hpp \
    ../../src/ProcessMemoryReader.hpp \
    ../../src/ModulesManager.hpp \
    ../../src/ModuleId.hpp \
    ../../src/Module.hpp \
    ../../src/HealRule.hpp \
    ../../src/Healer.hpp \
    ../../src/Configs.hpp \
    ../../src/Addresses.hpp \
    ../../src/TibiaFinder.hpp \
    ../../src/HealerRulesTable.hpp \
    ../../src/ConfigFromUiGenerator.hpp \
    ../../src/BotCore.hpp \
    ../../src/Bot.hpp

FORMS    += mainwindow.ui

win32:LIBS += -luser32
win32:LIBS += -lpsapi
win32:LIBS += -lkernel32
