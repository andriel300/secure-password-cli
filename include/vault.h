#pragma once

#include <stddef.h>

#define MAX_ENTRIES 100
#define MAX_STRING 256

typedef struct {
  int id;
  char name[MAX_STRING];
  char username[MAX_STRING];
  char password[MAX_STRING];
  char url[MAX_STRING];
  char notes[MAX_STRING];
} Entry;

typedef struct {
  Entry entries[MAX_ENTRIES];
  int count;
} VaultData;

// 🔐 Vault operations
int create_vault(const char *filename, const char *username,
                 const char *password);
int load_vault(const char *filename, const char *password,
               unsigned char *output, size_t output_size);
int save_vault(const char *filename, const char *password,
               const unsigned char *data, size_t data_len);
void free_vault(VaultData *vault);

// 🔗 JSON parser
int load_entries(const char *json, VaultData *vault);
char *save_entries_to_json(const VaultData *vault);

// 📜 CRUD operations
Entry *find_entry(VaultData *vault, int id);
void add_entry(VaultData *vault, const Entry *entry);
void delete_entry(VaultData *vault, int id);
