all: prog

prog: main.o func_api.o
	gcc -o prog main.o func_api.o
main.o: main.c func_api.h
	gcc -c -o main.o main.c
func_api.o: func_api.c func_api.h
	gcc -c -o func_api.o func_api.c
clean:
	rm -f *.o