@echo off
setlocal enabledelayedexpansion

echo 🔐 Installing Secure Password CLI for Windows...

:: ========================
:: 📦 Configurações
:: ========================
set "REPO=https://github.com/andriel300/secure-password-cli"
set "REPO_DIR=%USERPROFILE%\SecurePasswordCLI"
set "INSTALL_DIR=%USERPROFILE%\AppData\Local\SecurePasswordCLI"
set "BIN_DIR=%INSTALL_DIR%\bin"
set "APP_NAME=secure-password-cli"

:: ========================
:: 🔍 Verificar dependências
:: ========================
where git >nul 2>nul
if errorlevel 1 (
    echo ❌ Git not found. Please install Git for Windows from https://git-scm.com/download/win
    pause
    exit /b
)

where gcc >nul 2>nul
if errorlevel 1 (
    echo ❌ GCC not found. Please install MinGW-w64 from https://www.mingw-w64.org/
    pause
    exit /b
)

:: ========================
:: 📥 Clonar ou atualizar repositório
:: ========================
if not exist "%REPO_DIR%" (
    echo 📥 Cloning repository...
    git clone "%REPO%" "%REPO_DIR%"
) else (
    echo 🔄 Repository exists. Pulling latest changes...
    cd /d "%REPO_DIR%"
    git pull
)

:: ========================
:: ✔️ Criar diretórios
:: ========================
echo 📦 Creating install directories...
mkdir "%INSTALL_DIR%" >nul 2>nul
mkdir "%BIN_DIR%" >nul 2>nul

:: ========================
:: 📦 Copiar arquivos
:: ========================
echo 📦 Copying project files...
xcopy "%REPO_DIR%\*" "%INSTALL_DIR%\" /E /I /Y /EXCLUDE:exclude.txt >nul

:: ========================
:: ⚙️ Compilar
:: ========================
echo ⚙️ Compiling...
cd /D "%INSTALL_DIR%"
if exist "%BIN_DIR%\%APP_NAME%.exe" del "%BIN_DIR%\%APP_NAME%.exe"

gcc -Wall -Iinclude src\*.c cJSON\cJSON.c -o bin\%APP_NAME%.exe -lssl -lcrypto -mwindows

if not exist "bin\%APP_NAME%.exe" (
    echo ❌ Compilation failed.
    pause
    exit /b
)

:: ========================
:: 🔗 Adicionar ao PATH (se não estiver)
:: ========================
echo 🔗 Adding to PATH...
echo %PATH% | find /I "%BIN_DIR%" >nul
if errorlevel 1 (
    setx PATH "%PATH%;%BIN_DIR%"
    echo ✅ Added %BIN_DIR% to PATH.
) else (
    echo ℹ️ PATH already contains %BIN_DIR%.
)

:: ========================
:: 🖥️ Criar atalho na Área de Trabalho
:: ========================
echo 🖥️ Creating desktop shortcut...
powershell -Command ^
 "$s=(New-Object -COM WScript.Shell).CreateShortcut('%USERPROFILE%\Desktop\SecurePasswordCLI.lnk'); ^
 $s.TargetPath='%BIN_DIR%\%APP_NAME%.exe'; ^
 $s.IconLocation='%BIN_DIR%\%APP_NAME%.exe'; ^
 $s.Save()"

:: ========================
:: ✅ Concluído
:: ========================
echo.
echo ✅ Installed successfully!
echo ➡️ Run it from the Desktop or by typing: %APP_NAME%
pause
exit /b

