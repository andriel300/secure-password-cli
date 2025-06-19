CC = gcc
CFLAGS = -Wall -Iinclude -IcJSON
LDFLAGS = -lssl -lcrypto

SRC = src/main.c src/crypto.c src/vault.c src/json_parser.c cJSON/cJSON.c
OUT = secure-password-cli

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) vault.dat

