#include "gui.h"

// 🔃 Atualiza o conteúdo da tabela
void reload_vault_treeview() {
  GtkListStore *store =
      GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(vault_treeview)));
  gtk_list_store_clear(store);

  for (int i = 0; i < current_vault.count; i++) {
    GtkTreeIter iter;
    Entry *e = &current_vault.entries[i];

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, e->id, 1, e->name, 2, e->username, 3,
                       e->password, 4, e->url, 5, e->notes, -1);
  }
}

// ➕ Adicionar
void on_add_entry(GtkButton *button, gpointer user_data) {
  Entry new_entry = {
      .id = (current_vault.count > 0)
                ? current_vault.entries[current_vault.count - 1].id + 1
                : 1};

  strcpy(new_entry.name, "Novo Serviço");
  strcpy(new_entry.username, "usuario");
  strcpy(new_entry.password, "senha");
  strcpy(new_entry.url, "https://");
  strcpy(new_entry.notes, "Notas");

  add_entry(&current_vault, &new_entry);
  reload_vault_treeview();
}

// ✏️ Editar
void on_edit_entry(GtkButton *button, gpointer user_data) {
  GtkTreeSelection *selection =
      gtk_tree_view_get_selection(GTK_TREE_VIEW(vault_treeview));
  GtkTreeModel *model;
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    Entry *e = find_entry(&current_vault, id);

    if (e) {
      strcpy(e->password,
             "senha-editada"); // 🔥 Depois pode abrir popup para editar
      reload_vault_treeview();
    }
  }
}

// ❌ Deletar
void on_delete_entry(GtkButton *button, gpointer user_data) {
  GtkTreeSelection *selection =
      gtk_tree_view_get_selection(GTK_TREE_VIEW(vault_treeview));
  GtkTreeModel *model;
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    delete_entry(&current_vault, id);
    reload_vault_treeview();
  }
}

// 💾 Salvar
void on_save_vault(GtkButton *button, gpointer user_data) {
  char *json = save_entries_to_json(&current_vault);

  if (save_vault(current_vault_file, current_password,
                 (const unsigned char *)json, strlen(json))) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Vault salvo com sucesso!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }

  free(json);
}
