#include "gui.h"

// Widget global do TreeView
GtkWidget *vault_treeview;

// Cria a interface da aba Vault
GtkWidget *create_vault_page() {
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  // TreeView (Tabela)
  vault_treeview = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vault_treeview), TRUE);

  const char *columns[] = {"ID", "Nome", "Usuário", "Senha", "URL", "Notas"};
  for (int i = 0; i < 6; i++) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
        columns[i], renderer, "text", i, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(vault_treeview), column);
  }

  GtkListStore *store = gtk_list_store_new(6,
                                           G_TYPE_INT,    // ID
                                           G_TYPE_STRING, // Nome
                                           G_TYPE_STRING, // Usuário
                                           G_TYPE_STRING, // Senha
                                           G_TYPE_STRING, // URL
                                           G_TYPE_STRING  // Notas
  );
  gtk_tree_view_set_model(GTK_TREE_VIEW(vault_treeview), GTK_TREE_MODEL(store));
  g_object_unref(store);

  GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(scrolled), vault_treeview);
  gtk_widget_set_vexpand(scrolled, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

  // Botões de ações
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

  GtkWidget *btn_add = gtk_button_new_with_label("➕ Adicionar");
  g_signal_connect(btn_add, "clicked", G_CALLBACK(on_add_entry), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), btn_add, FALSE, FALSE, 0);

  GtkWidget *btn_edit = gtk_button_new_with_label("✏️ Editar");
  g_signal_connect(btn_edit, "clicked", G_CALLBACK(on_edit_entry), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), btn_edit, FALSE, FALSE, 0);

  GtkWidget *btn_delete = gtk_button_new_with_label("❌ Deletar");
  g_signal_connect(btn_delete, "clicked", G_CALLBACK(on_delete_entry), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), btn_delete, FALSE, FALSE, 0);

  GtkWidget *btn_save = gtk_button_new_with_label("💾 Salvar");
  g_signal_connect(btn_save, "clicked", G_CALLBACK(on_save_vault), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), btn_save, FALSE, FALSE, 0);

  reload_vault_treeview();

  return vbox;
}
