INC = -I../../sparky
CPP = *.cpp
OBJ = *.o
LIBP = -L../../bin/
LIB = -lsparky -lSDL2main -lSDL2 -lSDL2_image -lGLU -lGL -lGLEW -lm


all:
	g++ $(INC) -c $(CPP)
	g++ -o main $(OBJ) $(LIBP) $(LIB)
	./main

