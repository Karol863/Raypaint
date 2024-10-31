CC = gcc
SRC = $(wildcard *.c) $(wildcard *.h)
WARNINGS = -Wall -Wextra
INCLUDES = -lraylib
CFLAGS = $(WARNINGS) -march=native -O2 -flto -s -D_FORTIFY_SOURCE=1 $(INCLUDES)
DFLAGS = -g

build: $(SRC)
	$(CC) -o raypaint $(SRC) $(CFLAGS)

debug: $(SRC)
	$(CC) -o raypaint-debug $(SRC) $(DFLAGS) $(INCLUDES)
