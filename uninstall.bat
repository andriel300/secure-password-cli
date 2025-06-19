@echo off
setlocal

echo 🔥 Uninstalling Secure Password CLI...

:: Diretórios
set "INSTALL_DIR=%USERPROFILE%\AppData\Local\SecurePasswordCLI"
set "BIN_DIR=%INSTALL_DIR%\bin"
set "DESKTOP_SHORTCUT=%USERPROFILE%\Desktop\SecurePasswordCLI.lnk"

:: 🗑️ Remover arquivos e pastas
if exist "%INSTALL_DIR%" (
    echo 🗑️ Removing files from %INSTALL_DIR%
    rmdir /S /Q "%INSTALL_DIR%"
) else (
    echo ⚠️ Installation folder not found.
)

:: 🗑️ Remover shortcut da Área de Trabalho
if exist "%DESKTOP_SHORTCUT%" (
    echo 🗑️ Removing desktop shortcut
    del "%DESKTOP_SHORTCUT%"
)

:: 🚫 Remover do PATH (opcional)
:: Isso remove SOMENTE se estava no final do PATH. Para remoção segura manual é melhor.
for /f "tokens=2*" %%A in ('reg query "HKCU\Environment" /v PATH 2^>nul') do set OLD_PATH=%%B
set NEW_PATH=%OLD_PATH:;%BIN_DIR%=%
reg add "HKCU\Environment" /v PATH /d "%NEW_PATH%" /f >nul 2>&1

echo ✅ Uninstallation completed successfully!
pause

