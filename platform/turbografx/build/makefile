all: game.iso

include Make_game.inc

SRC = ../src/main.c ../../../game/game.c

CFLAGS ?= -v -O2 -fno-recursive -cd -over -gC

game.ovl: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS)
	cmd /c move ..\src\main.ovl game.ovl
	cmd /c copy ..\assets\bgm\title.wav title.wav
	cmd /c copy ..\assets\bgm\game.wav game.wav

game.iso: game.ovl
	$(IL) $@ -ipl="TurboSnake" $^ ..\assets\sfx\pickup.vox