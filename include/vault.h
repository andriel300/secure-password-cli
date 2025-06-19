#ifndef VAULT_H
#define VAULT_H

#include <stddef.h>

// Salvar dados no vault criptografado
int save_vault(const char *filename, const char *password, const unsigned char *plaintext, int plaintext_len);

// Carregar dados do vault criptografado
int load_vault(const char *filename, const char *password, unsigned char *plaintext, int max_plaintext_len);

#endif

