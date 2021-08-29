# Makefile for sorting algorith with function pointer
#TARGET = pfnsort
#LIBS = -lm
#SRCS = pfnsort.c alloc.c pfnsort.h
#OBJS = $(SRCS:.c=.o)
#HEAD = alloc.h
#CC = gcc
#CFLAGS = -g -Wall

#.PHONY: all clean

#all: $(TARGET)
#$TARGET: $(OBJS)
#			$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

#.c.o:
#		$(CC) $(CFLAGS) -c $< -o $@

#clean: rm -rf $(TARGET) $(OBJS)
pfnsort: pfnsort.o alloc.o
		gcc -o pfnsort pfnsort.o alloc.o -g

pfnsort.o: pfnsort.c
		gcc -c pfnsort.c -g

alloc.o: alloc.c
		gcc -c alloc.c -g

clean:
	rm -f *.o pfnsort
