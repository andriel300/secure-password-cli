CC = gcc
CFLAGS = -Wall -Iinclude

SRC = src/main.c src/generator.c src/validator.c src/utils.c src/breached.c src/entropy.c
OUT = secure-password-cli

ifeq ($(OS),Windows_NT)
    OUT := secure-password-cli.exe
endif

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lm

run: all
	./$(OUT)

clean:
	rm -f $(OUT)