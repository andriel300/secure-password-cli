# 📜 Documentação do Projeto — **Secure Password CLI GUI**
## Demo

![Demo](./bin/demo.gif)
## 🔐 Sobre o Projeto
**Secure Password CLI GUI** é um gerenciador de senhas simples, seguro e de código aberto. Com interface gráfica baseada em GTK, permite criar, salvar, desbloquear e gerenciar senhas locais em um vault criptografado usando **AES + PBKDF2 com OpenSSL**.

O projeto é construído em **C** com foco em aprendizado, segurança e simplicidade, e é uma evolução do projeto anterior em linha de comando (CLI), agora com interface gráfica (GUI).

## 🏗️ Tecnologias Utilizadas
- Linguagem C
- GTK+ 3
- OpenSSL
- cJSON

## 🚀 Funcionalidades
- 🔐 Criar vault criptografado
- 🔓 Desbloquear vault existente
- ➕ Adicionar entradas (nome, usuário, senha, URL, observações)
- ✏️ Editar entradas
- 🗑️ Excluir entradas
- 💾 Salvar vault criptografado localmente

## 📂 Estrutura de Pastas
```
.
├── src/                # Código fonte C
├── include/            # Arquivos de header (.h)
├── cJSON/              # Biblioteca de parser JSON
├── Makefile            # Script de build
├── README.md           # Documentação
└── CONTRIBUTING.md     # Guia para contribuidores
```

# 🔐 Secure Password CLI

Gerenciador de senhas seguro, criptografado, open-source, multiplataforma e com interface GTK.

---

## 🚀 Instalação

### 🔥 📦 Via Releases (Recomendado)

Baixe a versão mais recente na aba **[Releases](https://github.com/andriel300/secure-password-cli/releases)**:

- 🐧 `.deb` (Ubuntu, Debian, Linux Mint)
- 🐧 `.rpm` (Fedora, RHEL, openSUSE)
- 🐧 `.tar.gz` ou `.zip` (qualquer distribuição)
- 🪟 `.exe` (Windows) (em breve)

### Linux or MacOS
```bash
curl -O https://raw.githubusercontent.com/andriel300/secure-password-cli/main/install.sh
chmod +x install.sh
./install.sh
```
### Windows
```bash
curl -O https://raw.githubusercontent.com/andriel300/secure-password-cli/main/install.bat
chmod +x install.bat
./install.bat
```

## Desinstalação
```bash
rm -rf ~/.local/share/secure-password-cli
rm -f ~/.local/bin/secure-password-cli
rm -f ~/.local/share/applications/secure-password.desktop
```

```bash
./uninstall.sh  #or .bat if you're in windows.
```

### 👉 Linux (Manual via Git)

```bash
# Dependências (Debian/Ubuntu)
sudo apt install build-essential cmake libgtk-3-dev libssl-dev

# Clone o repositório
git clone https://github.com/andriel300/secure-password-cli.git
cd secure-password-cli

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Executar
./SecurePasswordCLI


## ❤️ Agradecimentos
Este projeto é uma oportunidade de aprendizado em desenvolvimento seguro e construção de interfaces gráficas com C.

---
