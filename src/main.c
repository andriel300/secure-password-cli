#include "gui.h"
#include "json_parser.h"
#include "vault.h"
#include <stdio.h>
#include <stdlib.h> // <-- Necessário para malloc, free
#include <string.h>

int main(int argc, char *argv[]) {
  start_gui(argc, argv);
  const char *filename = "vault.dat";
  const char *password = "minhasenhasecreta";

  // Dados a serem salvos (simulação)
  const char *data = "{ \"entries\": [ "
                     "{ \"id\": 1, \"name\": \"GitHub\", \"username\": "
                     "\"andriel\", \"password\": \"supersecreto\", \"url\": "
                     "\"https://github.com\", \"notes\": \"repo login\" }"
                     "] }";

  // 🔐 Salvar no vault
  if (save_vault(filename, password, (const unsigned char *)data,
                 strlen(data))) {
    printf("✅ Vault saved successfully!\n");
  } else {
    printf("❌ Failed to save vault.\n");
  }

  // 🔓 Ler do vault
  unsigned char output[4096];
  int len = load_vault(filename, password, output, sizeof(output));

  if (len > 0) {
    output[len] = '\0'; // Garantir null-terminated para string C

    // Parse JSON para estruturas C
    VaultData vault;
    if (load_entries((char *)output, &vault)) {
      printf("✔️ Found %zu entries.\n", vault.count);

      // Loop pelas entradas
      for (size_t i = 0; i < vault.count; i++) {
        Entry *e = &vault.entries[i];
        printf("🔑 [%d] %s - %s (%s)\n", e->id, e->name, e->username, e->url);
      }

      free_vault(&vault); // Libera memória
    } else {
      printf("❌ Failed to parse vault data.\n");
    }
  } else {
    printf("❌ Failed to open vault. Wrong password?\n");
  }
  VaultData vault;
  // Cria uma nova entrada
  Entry new_entry = {.id = 2,
                     .name = "Gmail",
                     .username = "andriel",
                     .password = "senha123",
                     .url = "https://gmail.com",
                     .notes = "Email pessoal"};
  add_entry(&vault, &new_entry);

  // Deletar entrada
  delete_entry(&vault, 1); // Remove entrada com id=1

  // Editar entrada
  Entry *e = find_entry(&vault, 2);
  if (e) {
    strcpy(e->password, "nova_senha_mega_segura");
  }

  // Salvar de volta no vault
  char *new_json = save_entries_to_json(&vault);

  if (save_vault(filename, password, (const unsigned char *)new_json,
                 strlen(new_json))) {
    printf("💾 Vault salvo com sucesso!\n");
  } else {
    printf("❌ Falha ao salvar vault.\n");
  }

  free(new_json);

  return 0;
}
