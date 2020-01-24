TARGET = c--

QT -= gui

CONFIG += c++14 -Werror
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++14

QMAKE_CC = g++
QMAKE_CXX = g++

DEFINES += \
    CPLUSPLUS \
    QT_DEPRECATED_WARNINGS \
    YY_NO_UNPUT

INCLUDEPATH += \
    Helpers \
    Nodes \
    Parser \
    .

DESTDIR = build
OBJECTS_DIR = obj
MOC_DIR = moc

SOURCES += \
    Helpers/util.cpp \
    Helpers/token.cpp \
    Nodes/constant_node.cpp \
    Nodes/error.cpp \
    Nodes/expression_node.cpp \
    Nodes/node.cpp \
    Nodes/program_node.cpp \
    Parser/lex.yy.c \
    Parser/parser.tab.c \
    main.cpp \
    Nodes/context.cpp \
    Nodes/declare_variable.cpp

HEADERS += \
    Helpers/util.h \
    Helpers/token.h \
    Nodes/constant_node.h \
    Nodes/error.h \
    Nodes/expression_node.h \
    Nodes/node.h \
    Nodes/program_node.h \
    Parser/lex_token.h \
    Parser/parser.tab.h \
    Nodes/context.h \
    Nodes/declare_variable.h
