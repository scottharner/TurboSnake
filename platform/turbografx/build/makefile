all: game.iso

include Make_game.inc

SRC = ../src/main.c ../../../game/game.c

CFLAGS ?= -v -O2 -fno-recursive -cd -gC

game.iso: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS)
	cmd /c move ..\src\main.iso game.iso
	cmd /c copy ..\assets\bgm\title.wav title.wav