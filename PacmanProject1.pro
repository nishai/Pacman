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
    tile.cpp \
    helpers.cpp \
    character.cpp \
    world.cpp \
    main.cpp

HEADERS += \
    texture.h \
    tile.h \
    helpers.h \
    character.h \
    world.h \
    window.h

DEFINES += SPRITEFILENAME=\\\"$$PWD/sprites.png\\\"
DEFINES += MAZEFILENAME=\\\"$$PWD/maze1.txt\\\"
