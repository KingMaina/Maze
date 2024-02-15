# Makefile for the project

# Variables
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
LDFLAGS = -lSDL2 -lm

CC = gcc
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = game
HEADERS = $(wildcard .include/*.h)

build:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)
lint:
	betty $(SRC) $(HEADERS)
clean:
	rm -f $(OBJ) $(EXEC)

run:
	./$(EXEC)
