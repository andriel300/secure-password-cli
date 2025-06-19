#!/bin/bash
set -e

echo "🗑️ Uninstalling Secure Password CLI..."

INSTALL_DIR="$HOME/.local/share/secure-password-cli"
DESKTOP_FILE="$HOME/.local/share/applications/secure-password.desktop"

# Remove files
rm -rf "$INSTALL_DIR"
rm -f "$DESKTOP_FILE"

echo "✅ Uninstalled successfully."
