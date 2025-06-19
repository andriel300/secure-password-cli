#ifndef VAULT_H
#define VAULT_H

// 🔐 Salvar vault criptografado
int save_vault(const char *filename, const char *password,
               const unsigned char *plaintext, int plaintext_len);

// 🔓 Carregar vault descriptografado
int load_vault(const char *filename, const char *password,
               unsigned char *output, int max_len);

// 🔧 Criar vault inicial
int create_vault(const char *filename, const char *username,
                 const char *password);

#endif
