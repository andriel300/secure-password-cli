#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>

// Deriva a chave da senha mestre
int derive_key(const char *password, const unsigned char *salt, unsigned char *key);

// Criptografa dados
int encrypt(const unsigned char *plaintext, int plaintext_len,
            const unsigned char *key, const unsigned char *iv,
            unsigned char *ciphertext);

// Descriptografa dados
int decrypt(const unsigned char *ciphertext, int ciphertext_len,
            const unsigned char *key, const unsigned char *iv,
            unsigned char *plaintext);

#endif

