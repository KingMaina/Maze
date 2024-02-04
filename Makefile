# Makefile for the project


# Variables
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -Iinclude/
LDFLAGS = -lSDL2

CC = gcc
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = game
HEADERS = $(wildcard ./src/*.h)

build:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

run:
	./$(EXEC)
