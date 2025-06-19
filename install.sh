#!/bin/bash
set -e

REPO_URL="https://github.com/andriel300/secure-password-cli"
REPO_DIR="$HOME/secure-password-cli"
INSTALL_DIR="$HOME/.local/share/secure-password-cli"
BIN_DIR="$HOME/.local/bin"
ICON_DIR="$HOME/.local/share/icons/hicolor/256x256/apps"
DESKTOP_FILE="$HOME/.local/share/applications/secure-password.desktop"
APP_NAME="secure-password-cli"

echo "🔐 Installing Secure Password CLI..."

# 📥 Clone or pull repo
if [ ! -d "$REPO_DIR" ]; then
	echo "📥 Cloning repository..."
	git clone "$REPO_URL" "$REPO_DIR"
else
	echo "🔄 Repository already exists. Pulling latest changes..."
	cd "$REPO_DIR"
	git pull
fi

cd "$REPO_DIR"

# 🖥️ Detect OS
OS="$(uname)"
echo "🖥️ Detected OS: $OS"

# 📦 Install dependencies
echo "📦 Checking for dependencies..."
if [[ "$OS" == "Linux" ]]; then
	if command -v apt &>/dev/null; then
		sudo apt update
		sudo apt install -y cmake build-essential pkg-config libgtk-3-dev libssl-dev rsync
	elif command -v pacman &>/dev/null; then
		sudo pacman -S --noconfirm cmake base-devel gtk3 openssl rsync
	elif command -v dnf &>/dev/null; then
		sudo dnf install -y cmake gcc make gtk3-devel openssl-devel rsync
	else
		echo "⚠️ Unknown package manager. Install cmake, gcc, gtk3, openssl manually."
	fi
elif [[ "$OS" == "Darwin" ]]; then
	if ! command -v brew &>/dev/null; then
		echo "🍎 Homebrew not found. Installing Homebrew..."
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
	fi
	brew install cmake pkg-config gtk+3 openssl
fi

# ✔️ Create install dirs
mkdir -p "$INSTALL_DIR"
mkdir -p "$BIN_DIR"
mkdir -p "$ICON_DIR"
mkdir -p "$(dirname "$DESKTOP_FILE")"

# ✔️ Copy files
echo "📦 Copying project files..."
rsync -a --exclude 'build' --exclude '*.o' --exclude '*.log' --exclude '*.out' . "$INSTALL_DIR"

cd "$INSTALL_DIR"

# ✔️ Build with CMake
echo "⚙️ Building..."
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)

# ✔️ Move binary
cp SecurePasswordCLI "$BIN_DIR/$APP_NAME"
chmod +x "$BIN_DIR/$APP_NAME"

# ✔️ Install icon
echo "🎨 Installing icon..."
cp "$INSTALL_DIR/assets/secure-password-cli.png" "$ICON_DIR/secure-password-cli.png"

# ✔️ Update icon cache
if command -v gtk-update-icon-cache &>/dev/null; then
	gtk-update-icon-cache "$HOME/.local/share/icons/hicolor" || true
	echo "🖼️ Icon cache updated."
fi

# ✔️ Create desktop entry (Linux)
if [[ "$OS" == "Linux" ]]; then
	echo "🖥️ Creating desktop entry..."

	cat >"$DESKTOP_FILE" <<EOL
[Desktop Entry]
Name=Secure Password CLI
Comment=Secure password manager with encryption
Exec=$BIN_DIR/$APP_NAME
Icon=secure-password-cli
Terminal=false
Type=Application
Categories=Utility;Security;
EOL

	chmod +x "$DESKTOP_FILE"
	echo "🟢 Desktop entry created at $DESKTOP_FILE"
fi

# ✔️ Shortcut for macOS
if [[ "$OS" == "Darwin" ]]; then
	echo "🍎 Creating Desktop shortcut..."
	ln -sf "$BIN_DIR/$APP_NAME" "$HOME/Desktop/$APP_NAME"
	echo "✅ You can launch it from Desktop or Terminal with: $APP_NAME"
fi

# ✔️ Check PATH
if [[ ":$PATH:" != *":$BIN_DIR:"* ]]; then
	echo "⚠️ Warning: $BIN_DIR is not in your PATH."
	echo "👉 Add it by adding this line to your ~/.bashrc, ~/.zshrc, or ~/.profile:"
	echo 'export PATH="$HOME/.local/bin:$PATH"'
fi

echo ""
echo "✅ Installed successfully!"
echo "➡️ Run it from the app menu (Rofi, Gnome, KDE, XFCE) or by typing:"
echo "   $APP_NAME"
