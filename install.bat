@echo off
setlocal

echo 🔐 Installing Secure Password CLI for Windows...

:: Diretórios
set "INSTALL_DIR=%USERPROFILE%\AppData\Local\SecurePasswordCLI"
set "BIN_DIR=%INSTALL_DIR%\bin"

:: Cria diretórios
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

:: Copia arquivos do projeto
echo 📦 Copying project files...
xcopy * "%INSTALL_DIR%\" /E /I /Y /EXCLUDE:exclude.txt

:: Compilar (Se usar MinGW ou GCC Windows)
echo ⚙️ Compiling...
cd /D "%INSTALL_DIR%"
gcc -Wall -Iinclude src\*.c cJSON\cJSON.c -o bin\secure-password-cli.exe -lssl -lcrypto -mwindows

:: ✔️ Adicionar ao PATH (opcional)
setx PATH "%PATH%;%BIN_DIR%"

:: ✔️ Criar atalho na Área de Trabalho (opcional)
echo 📄 Creating desktop shortcut...
powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%USERPROFILE%\Desktop\SecurePasswordCLI.lnk');$s.TargetPath='%BIN_DIR%\secure-password-cli.exe';$s.Save()"

echo.
echo ✅ Installed successfully!
echo ➡️ Run it from the Desktop or type: secure-password-cli
pause

