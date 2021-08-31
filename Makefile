

a.out: 
	gcc *.c $(sdl2-config --cflags --libs -lm -ldl) && ./a.out

