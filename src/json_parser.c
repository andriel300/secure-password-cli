#include "json_parser.h"
#include "cJSON.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_entries(const char *json_text, VaultData *vault) {
  cJSON *root = cJSON_Parse(json_text);
  if (!root) {
    fprintf(stderr, "JSON parsing error.\n");
    return 0;
  }

  cJSON *entries = cJSON_GetObjectItem(root, "entries");
  if (!cJSON_IsArray(entries)) {
    fprintf(stderr, "Entries not found or not an array.\n");
    cJSON_Delete(root);
    return 0;
  }

  int count = cJSON_GetArraySize(entries);
  vault->entries = malloc(sizeof(Entry) * count);
  vault->count = count;

  for (int i = 0; i < count; i++) {
    cJSON *item = cJSON_GetArrayItem(entries, i);
    Entry *e = &vault->entries[i];

    e->id = cJSON_GetObjectItem(item, "id")->valueint;

    strcpy(e->name, cJSON_GetObjectItem(item, "name")->valuestring);
    strcpy(e->username, cJSON_GetObjectItem(item, "username")->valuestring);
    strcpy(e->password, cJSON_GetObjectItem(item, "password")->valuestring);
    strcpy(e->url, cJSON_GetObjectItem(item, "url")->valuestring);
    strcpy(e->notes, cJSON_GetObjectItem(item, "notes")->valuestring);
  }

  cJSON_Delete(root);
  return 1;
}

void free_vault(VaultData *vault) {
  if (vault->entries) {
    free(vault->entries);
    vault->entries = NULL;
    vault->count = 0;
  }
}

// Adicionar entrada
void add_entry(VaultData *vault, const Entry *new_entry) {
  vault->entries = realloc(vault->entries, sizeof(Entry) * (vault->count + 1));
  vault->entries[vault->count] = *new_entry;
  vault->count++;
}

// Deletar entrada por ID
int delete_entry(VaultData *vault, int id) {
  size_t index = SIZE_MAX;
  for (size_t i = 0; i < vault->count; i++) {
    if (vault->entries[i].id == id) {
      index = i;
      break;
    }
  }

  if (index == SIZE_MAX) {
    return 0; // Não encontrado
  }

  for (size_t i = index; i < vault->count - 1; i++) {
    vault->entries[i] = vault->entries[i + 1];
  }

  vault->count--;
  vault->entries = realloc(vault->entries, sizeof(Entry) * vault->count);
  return 1; // Sucesso
}

// Buscar por ID:
Entry *find_entry(VaultData *vault, int id) {
  for (size_t i = 0; i < vault->count; i++) {
    if (vault->entries[i].id == id) {
      return &vault->entries[i];
    }
  }
  return NULL;
}

// Salvar VaultData para JSON String
char *save_entries_to_json(const VaultData *vault) {
  cJSON *root = cJSON_CreateObject();
  cJSON *entries = cJSON_CreateArray();

  for (size_t i = 0; i < vault->count; i++) {
    Entry *e = &vault->entries[i];
    cJSON *item = cJSON_CreateObject();

    cJSON_AddNumberToObject(item, "id", e->id);
    cJSON_AddStringToObject(item, "name", e->name);
    cJSON_AddStringToObject(item, "username", e->username);
    cJSON_AddStringToObject(item, "password", e->password);
    cJSON_AddStringToObject(item, "url", e->url);
    cJSON_AddStringToObject(item, "notes", e->notes);

    cJSON_AddItemToArray(entries, item);
  }

  cJSON_AddItemToObject(root, "entries", entries);

  char *json_str = cJSON_Print(root);
  cJSON_Delete(root);
  return json_str; // ⚠️ precisa ser liberado com free()
}
