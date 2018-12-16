SRC=sdlanim.c
BIN=sdlanim

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -o $(BIN) -lm -lSDLmain -lSDL -lSDL_ttf

clean:
	rm -f $(BIN)
