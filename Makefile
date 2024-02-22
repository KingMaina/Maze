build:
	gcc -std=c99 ./src/*.c -LlSDL2 -lSDL2 -lm -o game

run:
	./game

.PHONY: clean

clean:
	rm game
