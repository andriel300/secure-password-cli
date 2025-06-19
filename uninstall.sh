#!/bin/bash
set -e

echo "🗑️ Uninstalling Secure Password CLI..."

# 📦 Variáveis
INSTALL_DIR="$HOME/.local/share/secure-password-cli"
BIN_DIR="$HOME/.local/bin"
DESKTOP_FILE="$HOME/.local/share/applications/secure-password.desktop"
APP_NAME="secure-password-cli"

OS="$(uname)"

# ✔️ Remove binário
if [ -f "$BIN_DIR/$APP_NAME" ]; then
	rm "$BIN_DIR/$APP_NAME"
	echo "✅ Removed binary from $BIN_DIR/$APP_NAME"
fi

# ✔️ Remove pasta do projeto
if [ -d "$INSTALL_DIR" ]; then
	rm -rf "$INSTALL_DIR"
	echo "✅ Removed project folder from $INSTALL_DIR"
fi

# ✔️ Remove arquivo .desktop (Linux)
if [[ "$OS" == "Linux" ]]; then
	if [ -f "$DESKTOP_FILE" ]; then
		rm "$DESKTOP_FILE"
		echo "✅ Removed desktop entry $DESKTOP_FILE"
	fi
fi

# ✔️ Remove atalho da mesa (macOS)
if [[ "$OS" == "Darwin" ]]; then
	if [ -L "$HOME/Desktop/$APP_NAME" ]; then
		rm "$HOME/Desktop/$APP_NAME"
		echo "✅ Removed Desktop shortcut on macOS"
	fi
fi

echo ""
echo "✅ Uninstalled Secure Password CLI completely."
echo "➡️ If you installed it manually elsewhere, please check manually."
