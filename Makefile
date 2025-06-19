# 🔧 Compilador e flags
CC = gcc
CFLAGS = -Wall -Iinclude -IcJSON `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lssl -lcrypto

# 🗂️ Diretórios
SRC = src
BIN = bin
TARGET = $(BIN)/secure-password-cli

# 🔥 Arquivos fonte
SOURCES = \
	$(SRC)/main.c \
	$(SRC)/gui_globals.c \
	$(SRC)/gui_home.c \
	$(SRC)/gui_login.c \
	$(SRC)/gui_create_account.c \
	$(SRC)/gui_main_window.c \
	$(SRC)/gui_utils.c \
	$(SRC)/gui_page_vault.c \
	$(SRC)/gui_page_vault_events.c \
	$(SRC)/gui_page_generator.c \
	$(SRC)/gui_page_settings.c \
	$(SRC)/gui_footer.c \
	$(SRC)/generator.c \
	$(SRC)/crypto.c \
	$(SRC)/vault.c \
	$(SRC)/json_parser.c \
	cJSON/cJSON.c

# 🏗️ Build principal
all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BIN)
	@echo "⚙️  Compilando..."
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Build completo! Binário gerado em $(TARGET) 🚀"

# 🧹 Limpeza
clean:
	@rm -rf $(BIN)/*
	@echo "🧹 Binário limpo."

# 🧹 Limpeza total (incluindo obj se tiver)
clean-all:
	@rm -rf $(BIN) $(OBJ)
	@echo "🧽 Limpeza completa."

# 🎯 Executar
run: all
	@echo "🚀 Executando..."
	@./$(TARGET)

# 📦 Instalar (opcional)
install: all
	@mkdir -p ~/.local/bin
	@cp $(TARGET) ~/.local/bin/secure-password-cli
	@echo "✅ Instalado em ~/.local/bin/secure-password-cli"

# 🚫 Desinstalar
uninstall:
	@rm -f ~/.local/bin/secure-password-cli
	@echo "❌ Desinstalado de ~/.local/bin/secure-password-cli"

