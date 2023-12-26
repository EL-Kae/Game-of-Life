#My makefile for hw1

FLAGS = -std=c99 -Wall -g 

all: life

life: life.c
	gcc ${FLAGS} -o life life.c

clean:
	rm -f life
