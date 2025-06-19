@echo off
set INSTALL_DIR=%USERPROFILE%\AppData\Local\secure-password-cli

echo 🗑️ Uninstalling Secure Password CLI...

if exist "%INSTALL_DIR%" (
    rmdir /S /Q "%INSTALL_DIR%"
    echo ✅ Uninstalled successfully.
) else (
    echo ❌ Secure Password CLI is not installed.
)

pause

