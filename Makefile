CC = gcc
CFLAGS = -Wall -Iinclude -IcJSON
LDFLAGS = `pkg-config --libs gtk+-3.0` -lssl -lcrypto
GTKFLAGS = `pkg-config --cflags gtk+-3.0`

SRC = src/main.c src/gui.c src/crypto.c src/vault.c src/json_parser.c cJSON/cJSON.c
OUT = secure-password-cli

all:
	$(CC) $(CFLAGS) $(GTKFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) vault.dat

