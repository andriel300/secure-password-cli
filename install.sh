#!/bin/bash
set -e

echo "🔐 Installing Secure Password CLI..."

INSTALL_DIR="$HOME/.local/share/secure-password-cli"
DESKTOP_FILE="$HOME/.local/share/applications/secure-password.desktop"

# Create install directory
mkdir -p "$INSTALL_DIR"

# Copy files
cp -r * "$INSTALL_DIR"

cd "$INSTALL_DIR"

# Compile
echo "⚙️ Compiling..."
gcc -Wall -Iinclude src/*.c -o secure-password-cli -lm

# Create .desktop entry
echo "🖥️ Creating desktop entry..."
cat >"$DESKTOP_FILE" <<EOL
[Desktop Entry]
Name=Secure Password CLI
Comment=Generate secure passwords and check strength
Exec=$INSTALL_DIR/secure-password-cli
Icon=utilities-terminal
Terminal=true
Type=Application
Categories=Utility;
EOL

chmod +x "$DESKTOP_FILE"

echo "✅ Installed successfully to $INSTALL_DIR"
echo "➡️ You can run it from the app menu or with:"
echo "   $INSTALL_DIR/secure-password-cli"
