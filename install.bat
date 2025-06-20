@echo off
setlocal enabledelayedexpansion

echo Installing Secure Password CLI for Windows...

:: ========================
:: Configurations
:: ========================
set "REPO=https://github.com/andriel300/secure-password-cli"
set "REPO_DIR=%USERPROFILE%\SecurePasswordCLI"
set "INSTALL_DIR=%USERPROFILE%\AppData\Local\SecurePasswordCLI"
set "BIN_DIR=%INSTALL_DIR%\bin"
set "APP_NAME=secure-password-cli"

:: Path to MSYS2 (adjust if needed)
set "MSYS2_DIR=C:\msys64\ucrt64"
set "BIN_DEP=%MSYS2_DIR%\bin"

:: ========================
:: Check Dependencies
:: ========================
if not exist "%MSYS2_DIR%" (
    echo MSYS2 not found at %MSYS2_DIR%.
    echo Install MSYS2 from https://www.msys2.org/
    pause
    exit /b
)

where git >nul 2>nul
if errorlevel 1 (
    echo Git not found. Install from https://git-scm.com/download/win
    pause
    exit /b
)

where gcc >nul 2>nul
if errorlevel 1 (
    echo GCC not found. Install it with MSYS2: pacman -S mingw-w64-ucrt-x86_64-gcc
    pause
    exit /b
)

where pkg-config >nul 2>nul
if errorlevel 1 (
    echo pkg-config not found. Install it with: pacman -S mingw-w64-ucrt-x86_64-pkgconf
    pause
    exit /b
)

where windres >nul 2>nul
if errorlevel 1 (
    echo windres not found. Install it with: pacman -S mingw-w64-ucrt-x86_64-binutils
    pause
    exit /b
)

:: ========================
:: Clone or Update Repository
:: ========================
if not exist "%REPO_DIR%" (
    echo Cloning repository...
    git clone "%REPO%" "%REPO_DIR%"
) else (
    echo Repository exists. Pulling latest changes...
    cd /d "%REPO_DIR%"
    git pull
)

:: ========================
:: Create Folders
:: ========================
echo Creating install directories...
mkdir "%INSTALL_DIR%" >nul 2>nul
mkdir "%BIN_DIR%" >nul 2>nul

:: ========================
:: Copy Files
:: ========================
echo Copying project files...
xcopy "%REPO_DIR%\*" "%INSTALL_DIR%\" /E /I /Y >nul

:: ========================
:: Compile
:: ========================
echo Compiling...
cd /D "%INSTALL_DIR%"
if exist "%BIN_DIR%\%APP_NAME%.exe" del "%BIN_DIR%\%APP_NAME%.exe"

set PKG_CONFIG_PATH=%MSYS2_DIR%\lib\pkgconfig

for /f "delims=" %%i in ('pkg-config --cflags gtk+-3.0 openssl') do set "CFLAGS=%%i"
for /f "delims=" %%i in ('pkg-config --libs gtk+-3.0 openssl') do set "LIBS=%%i"

echo Compiling icon...
windres icon.rc -O coff -o icon.o

if not exist "icon.o" (
    echo Failed to compile icon. Check icon.rc and icon file path.
    pause
    exit /b
)

gcc -Wall -Iinclude -IcJSON %CFLAGS% ^
src\*.c cJSON\cJSON.c icon.o -o bin\%APP_NAME%.exe %LIBS% -mwindows

if not exist "bin\%APP_NAME%.exe" (
    echo Compilation failed. Check errors above.
    pause
    exit /b
)

del icon.o >nul 2>nul

:: ========================
:: Copy Runtime DLLs
:: ========================
echo Copying runtime DLLs...
xcopy "%BIN_DEP%\*.dll" "%BIN_DIR%\" /Y /I >nul

:: ========================
:: Add to PATH
:: ========================
echo Adding to PATH...
echo %PATH% | find /I "%BIN_DIR%" >nul
if errorlevel 1 (
    setx PATH "%PATH%;%BIN_DIR%"
    echo Added %BIN_DIR% to PATH.
) else (
    echo PATH already contains %BIN_DIR%.
)

:: ========================
:: Create Desktop Shortcut (Fixed)
:: ========================
echo Creating desktop shortcut...

set SHORTCUT=%TEMP%\CreateShortcut.ps1
del "%SHORTCUT%" >nul 2>nul

echo $Desktop = [Environment]::GetFolderPath("Desktop") >> "%SHORTCUT%"
echo $WshShell = New-Object -ComObject WScript.Shell >> "%SHORTCUT%"
echo $Shortcut = $WshShell.CreateShortcut("$Desktop\SecurePasswordCLI.lnk") >> "%SHORTCUT%"
echo $Shortcut.TargetPath = "%BIN_DIR%\%APP_NAME%.exe" >> "%SHORTCUT%"
echo $Shortcut.IconLocation = "%BIN_DIR%\%APP_NAME%.exe" >> "%SHORTCUT%"
echo $Shortcut.WorkingDirectory = "%BIN_DIR%" >> "%SHORTCUT%"
echo $Shortcut.Save() >> "%SHORTCUT%"

powershell -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile -File "%SHORTCUT%"
del "%SHORTCUT%"

:: ========================
:: Done
:: ========================
echo Installed successfully.
echo Run it from the Desktop or by typing: %APP_NAME%
pause
exit /b
