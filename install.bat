@echo off
setlocal enabledelayedexpansion

echo 🔐 Installing Secure Password CLI...

set INSTALL_DIR=%USERPROFILE%\AppData\Local\secure-password-cli

echo 📂 Installing to %INSTALL_DIR%

if not exist "%INSTALL_DIR%" (
    mkdir "%INSTALL_DIR%"
)

xcopy * "%INSTALL_DIR%" /E /I /Y

cd "%INSTALL_DIR%"

echo ⚙️ Compiling...

gcc -Wall -Iinclude src\*.c -o secure-password-cli.exe -lm

echo ✅ Installed successfully to %INSTALL_DIR%
echo ➡️ Run it with:
echo %INSTALL_DIR%\secure-password-cli.exe

pause

