CC  = g++
OUT = libsparky.a
INC = -I. -Ivendor/GLEW/include -Ivendor/SDL2_64bit/include

cmp:
	$(MAKE) --no-print-directory cmp_core
	$(MAKE) --no-print-directory cmp_window
	$(MAKE) --no-print-directory cmp_buffers
	$(MAKE) --no-print-directory cmp_shader
	$(MAKE) --no-print-directory cmp_camera
	$(MAKE) --no-print-directory cmp_texture
	$(MAKE) --no-print-directory cmp_renderer
	$(MAKE) --no-print-directory cmp_app
	$(MAKE) --no-print-directory build
	$(MAKE) --no-print-directory clean

reset:
	erase ..\bin\*.a 
	erase ..\bin\*.la 
	erase ..\bin\*.dll 

build:
	ar rcf $(OUT) *.o
	copy $(OUT) ..\bin
	copy vendor\GLEW\lib\* ..\bin
	copy vendor\SDL2_64bit\lib\* ..\bin
	copy vendor\GLEW\bin\*.dll ..\bin
	copy vendor\SDL2_64bit\bin\*.dll ..\bin
	
clean:
	erase *.o
	erase $(OUT)

cmp_core:
	$(CC) $(INC) -c core/*.cpp

cmp_window:
	$(CC) $(INC) -c window/*.cpp

cmp_buffers:
	$(CC) $(INC) -c buffers/*.cpp

cmp_shader:
	$(CC) $(INC) -c shader/*.cpp

cmp_camera:
	$(CC) $(INC) -c camera/*.cpp

cmp_texture:
	$(CC) $(INC) -c texture/*.cpp

cmp_renderer:
	$(CC) $(INC) -c renderer/quad_renderer/*.cpp

cmp_app:
	$(CC) $(INC) -c application/*.cpp

