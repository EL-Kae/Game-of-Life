#Makefile for game of life.

FLAGS = -std=c99 -Wall -g 

all: game_of_life

life: game_of_life.c
	gcc ${FLAGS} -o game_of_life game_of_life.c

clean:
	rm -f game_of_life
