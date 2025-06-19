#include "vault.h"
#include "crypto.h"
#include <openssl/rand.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho dos blocos
#define SALT_SIZE 16
#define IV_SIZE 16
#define KEY_SIZE 32

// Salvar vault criptografado no arquivo
int save_vault(const char *filename, const char *password,
               const unsigned char *plaintext, size_t plaintext_len) {
  FILE *file = fopen(filename, "wb");
  if (!file) {
    perror("Erro ao abrir o arquivo para escrita");
    return 0;
  }

  unsigned char salt[16];
  unsigned char iv[16];
  unsigned char key[32];

  RAND_bytes(salt, sizeof(salt));
  RAND_bytes(iv, sizeof(iv));
  derive_key(password, salt, key);

  int ciphertext_len = plaintext_len + 32;
  unsigned char *ciphertext = malloc(ciphertext_len);

  ciphertext_len = encrypt(plaintext, plaintext_len, key, iv, ciphertext);
  if (ciphertext_len <= 0) {
    fprintf(stderr, "Erro na criptografia\n");
    free(ciphertext);
    fclose(file);
    return 0;
  }

  fwrite(salt, 1, 16, file);
  fwrite(iv, 1, 16, file);
  fwrite(ciphertext, 1, ciphertext_len, file);

  fclose(file);
  free(ciphertext);
  return 1;
}

// Carregar vault e descriptografar
int load_vault(const char *filename, const char *password,
               unsigned char *plaintext, size_t max_plaintext_len) {
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

// 🔐 Salvar vault criptografado
int create_vault(const char *filename, const char *username,
                 const char *password) {
  char json_template[1024];
  snprintf(json_template, sizeof(json_template),
           "{ \"user\": \"%s\", \"entries\": [] }", username);

  return save_vault(filename, password, (const unsigned char *)json_template,
                    strlen(json_template));
}
