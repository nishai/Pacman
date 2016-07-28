OBJS=texture.cpp window.cpp

LFLAGS=-lSDL2 -lSDL2_image
CURRDIR=`pwd`
.PHONY: test

all: test
	
test: $(OBJS) test.o
	g++ -std=c++11 -Wall $(OBJS) test.o $(LFLAGS)

test.o: test.cpp
	g++ -c -std=c++11 -DSPRITEFILENAME="\"$(CURRDIR)/sprites.png\"" -Wall test.cpp -o test.o
