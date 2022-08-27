CC  = g++
OUT = libsparky.a
INC = -I.

cmp:
	$(MAKE) --no-print-directory cmp_core
	$(MAKE) --no-print-directory cmp_window
	$(MAKE) --no-print-directory cmp_app
	$(MAKE) --no-print-directory build
	$(MAKE) --no-print-directory clean

build:
	ar rcs $(OUT) *.o
	mv $(OUT) ../bin/

clean:
	rm *.o

cmp_core:
	$(CC) $(INC) -c core/*.cpp

cmp_window:
	$(CC) $(INC) -c window/*.cpp

cmp_app:
	$(CC) $(INC) -c application/*.cpp

