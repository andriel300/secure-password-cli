#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include "vault.h"
#include "crypto.h"

// Tamanho dos blocos
#define SALT_SIZE 16
#define IV_SIZE 16
#define KEY_SIZE 32

// Salvar vault criptografado no arquivo
int save_vault(const char *filename, const char *password, const unsigned char *plaintext, int plaintext_len) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 0;
    }

    // Gera salt e IV
    unsigned char salt[SALT_SIZE];
    unsigned char iv[IV_SIZE];
    unsigned char key[KEY_SIZE];

    if (!RAND_bytes(salt, sizeof(salt))) {
        fprintf(stderr, "Failed to generate salt\n");
        fclose(file);
        return 0;
    }

    if (!RAND_bytes(iv, sizeof(iv))) {
        fprintf(stderr, "Failed to generate IV\n");
        fclose(file);
        return 0;
    }

    // Deriva a chave
    derive_key(password, salt, key);

    // Buffer para dados criptografados
    int ciphertext_len = plaintext_len + 32;
    unsigned char *ciphertext = malloc(ciphertext_len);

    ciphertext_len = encrypt(plaintext, plaintext_len, key, iv, ciphertext);
    if (ciphertext_len <= 0) {
        fprintf(stderr, "Encryption failed\n");
        free(ciphertext);
        fclose(file);
        return 0;
    }

    // Escreve no arquivo: SALT + IV + CIPHERTEXT
    fwrite(salt, 1, SALT_SIZE, file);
    fwrite(iv, 1, IV_SIZE, file);
    fwrite(ciphertext, 1, ciphertext_len, file);

    fclose(file);
    free(ciphertext);
    return 1;
}

// Carregar vault e descriptografar
int load_vault(const char *filename, const char *password, unsigned char *plaintext, int max_plaintext_len) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return 0;
    }

    // Ler SALT e IV
    unsigned char salt[SALT_SIZE];
    unsigned char iv[IV_SIZE];
    unsigned char key[KEY_SIZE];

    fread(salt, 1, SALT_SIZE, file);
    fread(iv, 1, IV_SIZE, file);

    derive_key(password, salt, key);

    // Descobrir tamanho do ciphertext
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    long ciphertext_len = file_size - (SALT_SIZE + IV_SIZE);
    rewind(file);

    // Pula SALT e IV
    fseek(file, SALT_SIZE + IV_SIZE, SEEK_SET);

    // Ler o ciphertext
    unsigned char *ciphertext = malloc(ciphertext_len);
    fread(ciphertext, 1, ciphertext_len, file);
    fclose(file);

    // Descriptografar
    int decrypted_len = decrypt(ciphertext, ciphertext_len, key, iv, plaintext);

    if (decrypted_len <= 0) {
        fprintf(stderr, "Decryption failed or wrong password!\n");
        free(ciphertext);
        return 0;
    }

    // Garantir null-terminated se for texto
    if (decrypted_len < max_plaintext_len) {
        plaintext[decrypted_len] = '\0';
    }

    free(ciphertext);
    return decrypted_len;
}

