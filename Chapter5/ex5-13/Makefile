# Makefile for tail project

tail: tail.o alloc.o
		gcc -o tail tail.o alloc.o

tail.o: tail.c
		gcc -c tail.c

alloc.o: alloc.c
		gcc -c alloc.c

clean:
	rm -f *.o tail
