#include "generator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *generate_password(int length, int use_upper, int use_lower,
                        int use_numbers, int use_symbols, int min_numbers,
                        int min_symbols) {
  const char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *lower = "abcdefghijklmnopqrstuvwxyz";
  const char *numbers = "0123456789";
  const char *symbols = "!@#$%^&*";

  char pool[256] = {0};
  int pool_len = 0;

  if (use_upper) {
    strcat(pool, upper);
    pool_len += strlen(upper);
  }
  if (use_lower) {
    strcat(pool, lower);
    pool_len += strlen(lower);
  }
  if (use_numbers) {
    strcat(pool, numbers);
    pool_len += strlen(numbers);
  }
  if (use_symbols) {
    strcat(pool, symbols);
    pool_len += strlen(symbols);
  }

  if (pool_len == 0) {
    return NULL; // Nenhum caractere selecionado
  }

  if (length < min_numbers + min_symbols) {
    return NULL; // Não tem espaço suficiente
  }

  char *password = malloc(length + 1);
  if (!password) {
    return NULL;
  }

  srand((unsigned int)time(NULL) ^ (uintptr_t)&password);

  int pos = 0;

  // Garantir mínimos de números
  for (int i = 0; i < min_numbers; i++) {
    password[pos++] = numbers[rand() % strlen(numbers)];
  }

  // Garantir mínimos de símbolos
  for (int i = 0; i < min_symbols; i++) {
    password[pos++] = symbols[rand() % strlen(symbols)];
  }

  // Preencher o restante
  while (pos < length) {
    password[pos++] = pool[rand() % pool_len];
  }

  // Shuffle básico
  for (int i = 0; i < length; i++) {
    int j = rand() % length;
    char tmp = password[i];
    password[i] = password[j];
    password[j] = tmp;
  }

  password[length] = '\0';
  return password;
}
