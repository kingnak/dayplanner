QT += core network
QT -= gui

CONFIG += c++11

TARGET = BMICrawler
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    crawler.cpp \
    outputter.cpp \
    parser.cpp \
    rawdata.cpp

HEADERS += \
    crawler.h \
    outputter.h \
    parser.h
