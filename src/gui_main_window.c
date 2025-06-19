#include "gui.h"

void show_main_screen() {
  clear_main_container();

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(main_container), vbox);

  // TreeView (Tabela)
  treeview = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), TRUE);

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  // Definir colunas
  const char *titles[] = {"ID", "Nome", "Usuário", "URL", "Notas"};
  for (int i = 0; i < 5; i++) {
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(titles[i], renderer,
                                                      "text", i, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  }

  store = gtk_list_store_new(5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                             G_TYPE_STRING, G_TYPE_STRING);
  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
  g_object_unref(store);

  gtk_box_pack_start(GTK_BOX(vbox), treeview, TRUE, TRUE, 0);

  // Botões
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

  GtkWidget *add_btn = gtk_button_new_with_label("➕ Adicionar");
  g_signal_connect(add_btn, "clicked", G_CALLBACK(on_add_entry), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), add_btn, FALSE, FALSE, 0);

  GtkWidget *edit_btn = gtk_button_new_with_label("✏️ Editar");
  g_signal_connect(edit_btn, "clicked", G_CALLBACK(on_edit_entry), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), edit_btn, FALSE, FALSE, 0);

  GtkWidget *delete_btn = gtk_button_new_with_label("❌ Deletar");
  g_signal_connect(delete_btn, "clicked", G_CALLBACK(on_delete_entry), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), delete_btn, FALSE, FALSE, 0);

  GtkWidget *save_btn = gtk_button_new_with_label("💾 Salvar");
  g_signal_connect(save_btn, "clicked", G_CALLBACK(on_save_vault), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), save_btn, FALSE, FALSE, 0);

  GtkWidget *logout_btn = gtk_button_new_with_label("🔒 Logout");
  g_signal_connect(logout_btn, "clicked", G_CALLBACK(on_logout), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), logout_btn, FALSE, FALSE, 0);

  load_treeview_from_vault();

  gtk_widget_show_all(main_container);
}

void load_treeview_from_vault() {
  GtkListStore *store =
      GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
  gtk_list_store_clear(store);

  for (int i = 0; i < current_vault.count; i++) {
    GtkTreeIter iter;
    Entry *e = &current_vault.entries[i];

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, e->id, 1, e->name, 2, e->username, 3,
                       e->url, 4, e->notes, -1);
  }
}

// 🎯 Funções dos botões

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
  load_treeview_from_vault();
}

void on_edit_entry(GtkButton *button, gpointer user_data) {
  GtkTreeSelection *selection =
      gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
  GtkTreeModel *model;
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    Entry *e = find_entry(&current_vault, id);

    if (e) {
      strcpy(e->password, "senha-editada");
      load_treeview_from_vault();
    }
  }
}

void on_delete_entry(GtkButton *button, gpointer user_data) {
  GtkTreeSelection *selection =
      gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
  GtkTreeModel *model;
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    delete_entry(&current_vault, id);
    load_treeview_from_vault();
  }
}

void on_save_vault(GtkButton *button, gpointer user_data) {
  char *json = save_entries_to_json(&current_vault);

  if (save_vault(current_vault_file, current_password,
                 (const unsigned char *)json, strlen(json))) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Vault salvo com sucesso.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }

  free(json);
}

void on_logout(GtkButton *button, gpointer user_data) {
  free_vault(&current_vault);
  memset(current_password, 0, sizeof(current_password));
  memset(current_vault_file, 0, sizeof(current_vault_file));
  show_home_screen();
}
