SP = ../../sparky/
LINC = -I$(SP) -I$(SP)vendor/imgui/
CPP = *.cpp
OBJ = *.o
LIBP = -L../../bin/
LIB = -lsparky -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lGLEW -lm

all:
	g++ $(LINC) -c $(CPP)
	g++ -o main $(OBJ) $(LIBP) $(LIB)
	rm *.o
	./main

