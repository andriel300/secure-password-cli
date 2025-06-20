#pragma once
#include "vault.h" // ✅ Inclui a definição de Entry
#include <gtk/gtk.h>

// 🔃 Atualiza TreeView
void reload_vault_treeview(void);

// ➕ Adicionar
void on_add_entry(GtkButton *button, gpointer user_data);

// ✏️ Editar
void on_edit_entry(GtkButton *button, gpointer user_data);

// ❌ Deletar
void on_delete_entry(GtkButton *button, gpointer user_data);

// 💾 Salvar Vault
void on_save_vault(GtkButton *button, gpointer user_data);

// 🔥 Popup de Edição Profissional
void open_edit_entry_dialog(Entry *entry);
