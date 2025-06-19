#!/bin/bash
set -e

echo "🔐 Installing Secure Password CLI..."

# 📦 Variáveis
INSTALL_DIR="$HOME/.local/share/secure-password-cli"
BIN_DIR="$HOME/.local/bin"
DESKTOP_FILE="$HOME/.local/share/applications/secure-password.desktop"
APP_NAME="secure-password-cli"

# Detect OS
OS="$(uname)"
echo "🖥️ Detected OS: $OS"

# ✔️ Cria diretórios
mkdir -p "$INSTALL_DIR"
mkdir -p "$BIN_DIR"

# ✔️ Copia arquivos (ignora pastas desnecessárias)
echo "📦 Copying project files..."
rsync -a --exclude 'bin' --exclude '*.o' --exclude '*.out' --exclude '*.log' --exclude 'secure-password-cli' . "$INSTALL_DIR"

cd "$INSTALL_DIR"

# ✔️ Compila
echo "⚙️ Compiling..."
make clean || true
make

# ✔️ Move binário
cp bin/secure-password-cli "$BIN_DIR/$APP_NAME"
chmod +x "$BIN_DIR/$APP_NAME"

# ✔️ Verifica se ~/.local/bin está no PATH
if [[ ":$PATH:" != *":$BIN_DIR:"* ]]; then
	echo "⚠️ Warning: $BIN_DIR is not in your PATH."
	echo "👉 Add it by adding this line to your shell config:"
	echo 'export PATH="$HOME/.local/bin:$PATH"'
fi

# ✔️ Cria launcher (apenas Linux)
if [[ "$OS" == "Linux" ]]; then
	echo "🖥️ Creating desktop entry..."

	mkdir -p "$(dirname "$DESKTOP_FILE")"

	cat >"$DESKTOP_FILE" <<EOL
[Desktop Entry]
Name=Secure Password CLI
Comment=Secure password manager with encryption
Exec=$BIN_DIR/$APP_NAME
Icon=utilities-terminal
Terminal=false
Type=Application
Categories=Utility;Security;
EOL

	chmod +x "$DESKTOP_FILE"
	echo "🟢 Desktop entry created at $DESKTOP_FILE"
fi

# ✔️ Cria atalho no macOS (opcional)
if [[ "$OS" == "Darwin" ]]; then
	echo "🍎 macOS detected - creating launch shortcut..."
	ln -sf "$BIN_DIR/$APP_NAME" "$HOME/Desktop/$APP_NAME"
	echo "✅ You can launch it from Desktop or terminal with: $APP_NAME"
fi

echo ""
echo "✅ Installed successfully!"
echo "➡️ Run it from the app menu (Linux) or by typing:"
echo "   $APP_NAME"
