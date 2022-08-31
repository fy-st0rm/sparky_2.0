CC  = g++
OUT = libsparky.a
INC = -I.


cmp:
	$(MAKE) --no-print-directory cmp_core
	$(MAKE) --no-print-directory cmp_window
	$(MAKE) --no-print-directory cmp_buffers
	$(MAKE) --no-print-directory cmp_shader
	$(MAKE) --no-print-directory cmp_texture
	$(MAKE) --no-print-directory cmp_renderer
	$(MAKE) --no-print-directory cmp_app
	$(MAKE) --no-print-directory build
	$(MAKE) --no-print-directory clean

build:
	ar rcf $(OUT) *.o
	mv $(OUT) ../bin/

clean:
	rm *.o

cmp_core:
	$(CC) $(INC) -c core/*.cpp

cmp_window:
	$(CC) $(INC) -c window/*.cpp

cmp_buffers:
	$(CC) $(INC) -c buffers/*.cpp

cmp_shader:
	$(CC) $(INC) -c shader/*.cpp

cmp_texture:
	$(CC) $(INC) -c texture/*.cpp

cmp_renderer:
	$(CC) $(INC) -c renderer/*.cpp

cmp_app:
	$(CC) $(INC) -c application/*.cpp

