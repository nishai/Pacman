TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wall

LIBS += -lSDL2 -lSDL2_image

SOURCES += \
    texture.cpp \
    window.cpp \
    test.cpp

HEADERS += \
    texture.h \
    window.h

DEFINES += SPRITEFILENAME=\\\"$$PWD/sprites.png\\\"
