#pragma once
#include "vault.h" //
#include <gtk/gtk.h>

// 🔃 Atualiza o TreeView com os dados do current_vault
void reload_vault_treeview(void);

// ➕ Adicionar uma nova entrada
void on_add_entry(GtkButton *button, gpointer user_data);

// ✏️ Editar uma entrada selecionada
void on_edit_entry(GtkButton *button, gpointer user_data);

// ❌ Deletar uma entrada selecionada
void on_delete_entry(GtkButton *button, gpointer user_data);

// 💾 Salvar o vault criptografado no disco
void on_save_vault(GtkButton *button, gpointer user_data);

// 🔥 Abre o popup de edição (usado tanto para adicionar quanto editar)
// Se 'entry' for NULL → cria uma nova entrada
// Se 'entry' não for NULL → edita a entrada existente
void open_edit_entry_dialog(Entry *entry);
