INC = -I../../sparky
CPP = *.cpp
OBJ = *.o
LIBP = -L../../bin/
LIB = -lsparky -lmingw32 -lopengl32 -lUser32 -lGdi32 -lShell32 -lglew32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -imm32

all:
	g++ $(INC) -c $(CPP)
	g++ -o main $(OBJ) $(LIBP) $(LIB)
	erase *.o
	main.exe

