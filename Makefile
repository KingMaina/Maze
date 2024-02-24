build:
	gcc -std=c99 ./src/*.c -lSDL2 -lm -o game

run:
	./game

.PHONY: clean

clean:
	rm game
