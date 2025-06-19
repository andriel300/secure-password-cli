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

  char charset[256] = {0};
  size_t charset_len = 0;

  if (use_upper) {
    strcat(charset, upper);
    charset_len += strlen(upper);
  }
  if (use_lower) {
    strcat(charset, lower);
    charset_len += strlen(lower);
  }
  if (use_numbers) {
    strcat(charset, numbers);
    charset_len += strlen(numbers);
  }
  if (use_symbols) {
    strcat(charset, symbols);
    charset_len += strlen(symbols);
  }

  if (charset_len == 0) {
    return NULL; // Nenhum charset selecionado
  }

  if (length < min_numbers + min_symbols) {
    return NULL; // Comprimento muito curto para atender os mínimos
  }

  char *password = malloc(length + 1);
  if (!password)
    return NULL;

  srand((unsigned int)time(NULL) ^ (uintptr_t)&password);

  int pos = 0;

  // ✅ Garante mínimo de números
  for (int i = 0; i < min_numbers; i++) {
    password[pos++] = numbers[rand() % strlen(numbers)];
  }

  // ✅ Garante mínimo de símbolos
  for (int i = 0; i < min_symbols; i++) {
    password[pos++] = symbols[rand() % strlen(symbols)];
  }

  // 🔥 Preencher o restante
  for (; pos < length; pos++) {
    password[pos] = charset[rand() % charset_len];
  }

  // 🔀 Embaralhar (shuffle)
  for (int i = length - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    char tmp = password[i];
    password[i] = password[j];
    password[j] = tmp;
  }

  password[length] = '\0';
  return password;
}
