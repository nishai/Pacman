SRC=texture.cpp window.cpp tile.cpp main.cpp helpers.cpp character.cpp
OBJ=$(SRC:%.cpp=%.o)

LFLAGS=-lSDL2 -lSDL2_image
CURRDIR=`pwd`
CXX=g++ -std=c++11 -DSPRITEFILENAME="\"$(CURRDIR)/sprites.png\"" -Wall

all: $(OBJ)
	$(CXX) $(OBJ) $(LFLAGS)

%.o: %.c
	$(CXX) $@ -c $< # if .cpp changed, recompile .o
