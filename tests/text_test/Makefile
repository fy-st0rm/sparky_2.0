SP = ../../sparky/
LINC = -I$(SP) -I$(SP)vendor/GLEW/include -I$(SP)vendor/SDL2_64bit/include -I$(SP)vendor/SDL2_64bit/include/SDL2 -I$(SP)vendor/imgui/
CPP = *.cpp
OBJ = *.o
LIBP = -L../../bin/
LIB = -lsparky -lmingw32 -lopengl32 -lUser32 -lGdi32 -lShell32 -lglew32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -limm32

all:
	g++ $(LINC) -c $(CPP)
	g++ -o main $(OBJ) $(LIBP) $(LIB)
	erase *.o
	main.exe

