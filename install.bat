@echo off
setlocal

REM 🔗 Variáveis
set REPO_URL=https://github.com/andriel300/secure-password-cli
set REPO_DIR=%USERPROFILE%\secure-password-cli
set INSTALL_DIR=%USERPROFILE%\AppData\Local\SecurePasswordCLI
set BIN_DIR=%INSTALL_DIR%\bin
set APP_NAME=secure-password-cli
set ICON=%INSTALL_DIR%\assets\icon-transparent-bg.ico

echo 🔐 Installing Secure Password CLI for Windows...

REM 📥 Clonar o repositório
if not exist "%REPO_DIR%" (
    echo 📥 Cloning repository...
    git clone %REPO_URL% "%REPO_DIR%"
) else (
    echo 🔄 Repository already exists. Pulling latest changes...
    cd /d "%REPO_DIR%"
    git pull
)

cd /d "%REPO_DIR%"

REM ✔️ Criar diretórios
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

REM 📦 Copiar arquivos
echo 📦 Copying project files...
robocopy . "%INSTALL_DIR%" /MIR /XD build /XF *.o *.out *.log /NFL /NDL /NJH /NJS /nc /ns /np

cd /d "%INSTALL_DIR%"

REM ⚙️ Compilar
echo ⚙️ Compiling...

if exist "%BIN_DIR%\%APP_NAME%.exe" (
    del "%BIN_DIR%\%APP_NAME%.exe"
)

gcc -Wall -Iinclude src\*.c cJSON\cJSON.c -o bin\%APP_NAME%.exe -lssl -lcrypto -mwindows

if %errorlevel% neq 0 (
    echo ❌ Compilation failed. Make sure MinGW-w64 and OpenSSL are installed.
    pause
    exit /b
)

REM ✔️ Adicionar ao PATH
set PATH=%PATH%;%BIN_DIR%
setx PATH "%PATH%"

REM 📄 Criar atalho na área de trabalho
echo 📄 Creating desktop shortcut...
powershell -Command ^
 "$s = (New-Object -COM WScript.Shell).CreateShortcut('%USERPROFILE%\Desktop\SecurePasswordCLI.lnk'); ^
  $s.TargetPath = '%BIN_DIR%\%APP_NAME%.exe'; ^
  $s.IconLocation = '%ICON%'; ^
  $s.Save()"

echo.
echo ✅ Installed successfully!
echo 🚀 Run it from the Desktop or terminal with: %APP_NAME%
pause

