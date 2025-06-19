CC = gcc
CFLAGS = -Wall -Iinclude

SRC = src/main.c src/generator.c src/validator.c src/utils.c
OUT = secure-password-cli

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)

