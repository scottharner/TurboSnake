all: game.pce

include Make_game.inc

SRC = ../src/main.c

CFLAGS ?= -v -O2 -fno-recursive -gC

game.pce: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS)
	cmd /c move ..\src\main.pce game.pce

clean::
	rm -f game.pce