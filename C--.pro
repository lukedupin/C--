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
    Nodes/call_node.cpp \
    Nodes/construct_node.cpp \
    Nodes/klass_node.cpp \
    Nodes/op_node.cpp \
    Nodes/block_node.cpp \
    Nodes/constant_node.cpp \
    Nodes/error.cpp \
    Nodes/function_node.cpp \
    Nodes/if_node.cpp \
    Nodes/node.cpp \
    Nodes/param_node.cpp \
    Nodes/program_node.cpp \
    Nodes/simple_node.cpp \
    Parser/lex.yy.c \
    Parser/parser.tab.c \
    main.cpp \
    Nodes/context.cpp \
    Nodes/declare_node.cpp

HEADERS += \
    Helpers/util.h \
    Helpers/token.h \
    Nodes/call_node.h \
    Nodes/construct_node.h \
    Nodes/klass_node.h \
    Nodes/op_node.h \
    Nodes/block_node.h \
    Nodes/constant_node.h \
    Nodes/error.h \
    Nodes/function_node.h \
    Nodes/if_node.h \
    Nodes/node.h \
    Nodes/param_node.h \
    Nodes/program_node.h \
    Nodes/simple_node.h \
    Parser/lex_token.h \
    Parser/parser.tab.h \
    Nodes/context.h \
    Nodes/declare_node.h
