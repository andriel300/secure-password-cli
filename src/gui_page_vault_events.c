#include "gui_page_vault_events.h"
#include "generator.h"
#include "gui.h"
#include <stdlib.h>
#include <string.h>

// 🔥 Struct para toggle de senha
typedef struct {
  GtkEntry *entry;
  gboolean visible;
} PasswordToggleData;

// 🔃 Atualiza o TreeView
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
  open_edit_entry_dialog(NULL); // NULL = novo
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
      open_edit_entry_dialog(e);
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

// 💾 Salvar Vault no disco
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

// 🔥 Mostrar/Ocultar senha
void on_toggle_password_clicked(GtkButton *button, gpointer user_data) {
  PasswordToggleData *data = (PasswordToggleData *)user_data;

  data->visible = !data->visible;
  gtk_entry_set_visibility(GTK_ENTRY(data->entry), data->visible);

  gtk_button_set_label(GTK_BUTTON(button), data->visible ? "🙈" : "👁️");
}

// 🎲 Gerar senha
void on_generate_password_clicked(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);

  char *password = generate_password(16, TRUE, TRUE, TRUE, TRUE, 1, 1);
  gtk_entry_set_text(entry, password);
  free(password);
}

// 🔥 Popup de criar/editar entrada
void open_edit_entry_dialog(Entry *entry) {
  gboolean is_new = (entry == NULL);

  Entry temp_entry;
  if (is_new) {
    temp_entry.id = (current_vault.count > 0)
                        ? current_vault.entries[current_vault.count - 1].id + 1
                        : 1;
    strcpy(temp_entry.name, "");
    strcpy(temp_entry.username, "");
    strcpy(temp_entry.password, "");
    strcpy(temp_entry.url, "https://");
    strcpy(temp_entry.notes, "");
    entry = &temp_entry;
  }

  GtkWidget *dialog;
  GtkWidget *content_area;
  GtkWidget *grid;

  dialog = gtk_dialog_new_with_buttons(
      is_new ? "➕ Nova Entrada" : "✏️ Editar Entrada", GTK_WINDOW(window),
      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "Salvar",
      GTK_RESPONSE_OK, "Cancelar", GTK_RESPONSE_CANCEL, NULL);

  content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 12);
  gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
  gtk_container_add(GTK_CONTAINER(content_area), grid);

  // Labels e Entries
  GtkWidget *label_name = gtk_label_new("Nome:");
  GtkWidget *entry_name = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_name), entry->name);

  GtkWidget *label_username = gtk_label_new("Usuário:");
  GtkWidget *entry_username = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_username), entry->username);

  GtkWidget *label_password = gtk_label_new("Senha:");

  GtkWidget *hbox_password = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  GtkWidget *entry_password = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_password), entry->password);
  gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
  gtk_widget_set_hexpand(entry_password, TRUE);

  GtkWidget *btn_toggle_password = gtk_button_new_with_label("👁️");
  gtk_widget_set_tooltip_text(btn_toggle_password, "Mostrar/Ocultar Senha");

  GtkWidget *btn_generate_password = gtk_button_new_with_label("🎲");
  gtk_widget_set_tooltip_text(btn_generate_password, "Gerar Senha Aleatória");

  gtk_box_pack_start(GTK_BOX(hbox_password), entry_password, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox_password), btn_toggle_password, FALSE, FALSE,
                     0);
  gtk_box_pack_start(GTK_BOX(hbox_password), btn_generate_password, FALSE,
                     FALSE, 0);

  GtkWidget *label_url = gtk_label_new("URL:");
  GtkWidget *entry_url = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_url), entry->url);

  GtkWidget *label_notes = gtk_label_new("Notas:");
  GtkWidget *entry_notes = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_notes), entry->notes);

  // Layout no grid
  gtk_grid_attach(GTK_GRID(grid), label_name, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry_name, 1, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), label_username, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry_username, 1, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), label_password, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), hbox_password, 1, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), label_url, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry_url, 1, 3, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), label_notes, 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry_notes, 1, 4, 1, 1);

  gtk_widget_show_all(dialog);

  // 🔗 Toggle 👁️ e Gerar Senha
  PasswordToggleData *toggle_data = g_malloc(sizeof(PasswordToggleData));
  toggle_data->entry = GTK_ENTRY(entry_password);
  toggle_data->visible = FALSE;

  g_signal_connect(btn_toggle_password, "clicked",
                   G_CALLBACK(on_toggle_password_clicked), toggle_data);

  g_signal_connect(btn_generate_password, "clicked",
                   G_CALLBACK(on_generate_password_clicked), entry_password);

  // 🔥 Dialog
  gint response = gtk_dialog_run(GTK_DIALOG(dialog));
  if (response == GTK_RESPONSE_OK) {
    const char *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *username = gtk_entry_get_text(GTK_ENTRY(entry_username));

    if (strlen(name) == 0 || strlen(username) == 0) {
      GtkWidget *error_dialog = gtk_message_dialog_new(
          GTK_WINDOW(dialog), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
          GTK_BUTTONS_OK, "Nome e Usuário não podem estar vazios.");
      gtk_dialog_run(GTK_DIALOG(error_dialog));
      gtk_widget_destroy(error_dialog);
    } else {
      // 🔥 Atualiza dados
      strncpy(entry->name, name, sizeof(entry->name) - 1);
      strncpy(entry->username, username, sizeof(entry->username) - 1);
      strncpy(entry->password, gtk_entry_get_text(GTK_ENTRY(entry_password)),
              sizeof(entry->password) - 1);
      strncpy(entry->url, gtk_entry_get_text(GTK_ENTRY(entry_url)),
              sizeof(entry->url) - 1);
      strncpy(entry->notes, gtk_entry_get_text(GTK_ENTRY(entry_notes)),
              sizeof(entry->notes) - 1);

      if (is_new) {
        add_entry(&current_vault, entry);
      }

      reload_vault_treeview();
    }
  }

  g_free(toggle_data);
  gtk_widget_destroy(dialog);
}
