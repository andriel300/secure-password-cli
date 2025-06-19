# 🗒️ TODO - Secure Password CLI

Este documento lista as funcionalidades, melhorias e ideias futuras para o desenvolvimento do Secure Password CLI.

---

## 🚀 Funcionalidades Prioritárias

- [ ] 🔐 Sistema de pesquisa no Vault (buscar por nome, usuário, URL)
- [ ] 🗂️ Categorias/Tags para organizar senhas
- [ ] 🛠️ Editor completo de entradas (editar todos os campos, não só senha)
- [ ] 📜 Histórico de senhas (armazenar versões anteriores opcional)
- [ ] 🗑️ Lixeira para itens deletados (recuperação rápida)
- [ ] 🔒 Timeout para auto-lock do vault após X minutos
- [ ] 🔑 Autenticação com chave mestra + opcional chave hardware (Yubikey/FIDO2)
- [ ] 📤 Importar senhas de CSV, JSON, Bitwarden, KeePass, etc.
- [ ] 📥 Exportar senhas para CSV ou JSON com alerta de segurança

---

## 🎨 Melhorias de Interface (UI/UX)

- [ ] 🎨 Interface com temas claros e escuros
- [ ] 🧭 Barra lateral com atalhos rápidos (Vault, Gerador, Configurações)
- [ ] ⚙️ Tela de configurações com preferências (tema, timeout, etc.)
- [ ] 📏 Layout responsivo e centralizado
- [ ] 🖼️ Ícones e visual moderno (já possui `/assets`)
- [ ] 🔔 Notificações visuais (senha copiada, erro, salvo, etc.)

---

## 🔐 Melhorias de Segurança

- [ ] 🔐 Implementar verificação de senha vazada (API Have I Been Pwned)
- [ ] 📊 Cálculo de entropia da senha
- [ ] 🚫 Proteção contra brute-force (limite de tentativas)
- [ ] 🛡️ Suporte a arquivos vault criptografados com Argon2 (opcional ao PBKDF2 atual)
- [ ] 💣 Botão de emergência: Apagar o vault rapidamente
- [ ] 🧠 Criptografia na memória enquanto executa

---

## 🌐 Funcionalidades Futuras

- [ ] ☁️ Integração opcional com armazenamento na nuvem (Google Drive, Dropbox, etc.)
- [ ] 📱 Versão mobile (GTK ou outra tecnologia)
- [ ] 🔗 Sincronização entre dispositivos
- [ ] 🔧 Interface Web (via localhost ou Electron opcional)
- [ ] 🌍 Traduções (PT-BR, EN, ES, etc.)

---

## 📦 Distribuição

- [x] 🐧 .DEB (Debian/Ubuntu)
- [x] 🎩 .RPM (Fedora, RHEL, openSUSE)
- [x] 📦 .tar.gz
- [x] 🪟 .exe (NSIS installer)
- [x] 🍏 .dmg (macOS)
- [ ] 🅰️ AUR package (Arch Linux) (⏳ Planejado para versão alpha)
- [ ] 🐋 Docker container
- [ ] 📦 Flatpak / Snap

---

## 🏗️ Manutenção e Infraestrutura

- [ ] 🧹 Refatoração completa do código para maior modularidade
- [ ] 🧪 Implementação de testes unitários (funções críticas: crypto, vault, json)
- [ ] 🤖 Pipeline de CI/CD (GitHub Actions)
- [ ] 📄 Documentação detalhada para devs e usuários
- [ ] 📜 Licença clara no repositório (MIT, GPL, etc.)

---

## 💡 Ideias Futuras

- [ ] 🔐 Suporte a cofres múltiplos
- [ ] 🗺️ Modo offline e modo portátil (executável standalone)
- [ ] 🖥️ Integração com rofi/dmenu
- [ ] 🎛️ Widget para desktop (mostrar senha temporária)

---

## 👾 Contribuições

Sugestões, melhorias e PRs são super bem-vindos! Abra uma issue ou mande um PR!

---
