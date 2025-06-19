#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stddef.h>

typedef struct {
  int id;
  char name[256];
  char username[256];
  char password[256];
  char url[512];
  char notes[512];
} Entry;

typedef struct {
  Entry *entries;
  size_t count;
} VaultData;

// Carregar do JSON para VaultData
int load_entries(const char *json_text, VaultData *vault);

// Salvar VaultData para JSON (gera string JSON)
char *save_entries_to_json(const VaultData *vault);

// Liberar memória
void free_vault(VaultData *vault);

// CRUD
void add_entry(VaultData *vault, const Entry *new_entry);
int delete_entry(VaultData *vault, int id);
Entry *find_entry(VaultData *vault, int id);

#endif
