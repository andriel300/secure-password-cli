CC = gcc
CFLAGS = -Wall -Iinclude -IcJSON `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lssl -lcrypto

SRC = src/main.c \
			src/gui_globals.c \
			src/gui_home.c \
			src/gui_login.c \
      src/gui_create_account.c \
			src/gui_main_window.c \
			src/gui_utils.c \
			src/crypto.c \
      src/vault.c \
			src/json_parser.c \
			cJSON/cJSON.c

OUT = secure-password-cli

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)

