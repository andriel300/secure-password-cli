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

## 🏃‍♂️ Como Executar
```bash
sudo apt install libgtk-3-dev libssl-dev
make
./secure-password-cli
```

## ❤️ Agradecimentos
Este projeto é uma oportunidade de aprendizado em desenvolvimento seguro e construção de interfaces gráficas com C.

---
