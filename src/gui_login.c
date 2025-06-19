#include "gui.h"

// 🔓 Tela de Login (UI melhorada)
void show_login_screen() {
  clear_main_container();

  // 🔳 Container principal (VBox)
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
  gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 30);
  gtk_container_add(GTK_CONTAINER(main_container), vbox);

  // 🔖 Título
  GtkWidget *label = gtk_label_new(NULL);
  gtk_label_set_markup(
      GTK_LABEL(label),
      "<span size='20000' weight='bold'>🔐 Desbloquear Vault</span>");
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

  // 🧠 Grid do formulário
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

  // 🔤 Username
  GtkWidget *label_user = gtk_label_new("Nome de Usuário:");
  gtk_widget_set_halign(label_user, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), label_user, 0, 0, 1, 1);

  entry_login_username = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_login_username),
                                 "Seu nome de usuário");
  gtk_grid_attach(GTK_GRID(grid), entry_login_username, 1, 0, 1, 1);

  // 🔑 Password
  GtkWidget *label_pass = gtk_label_new("Senha Mestre:");
  gtk_widget_set_halign(label_pass, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 1, 1, 1);

  entry_login_password = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(entry_login_password), FALSE);
  gtk_entry_set_invisible_char(GTK_ENTRY(entry_login_password), 0x2022);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_login_password),
                                 "Sua senha mestre");
  gtk_grid_attach(GTK_GRID(grid), entry_login_password, 1, 1, 1, 1);

  // 🚀 Botões
  GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);

  GtkWidget *unlock_btn = gtk_button_new_with_label("🔓 Desbloquear Vault");
  g_signal_connect(unlock_btn, "clicked", G_CALLBACK(on_login_confirm), NULL);
  gtk_box_pack_start(GTK_BOX(button_box), unlock_btn, FALSE, FALSE, 0);

  GtkWidget *back_btn = gtk_button_new_with_label("⬅️ Voltar");
  g_signal_connect(back_btn, "clicked", G_CALLBACK(show_home_screen), NULL);
  gtk_box_pack_start(GTK_BOX(button_box), back_btn, FALSE, FALSE, 0);

  gtk_widget_show_all(main_container);
}

// 🔑 Lógica de autenticação
void on_login_confirm(GtkButton *button, gpointer user_data) {
  const char *username = gtk_entry_get_text(GTK_ENTRY(entry_login_username));
  const char *password = gtk_entry_get_text(GTK_ENTRY(entry_login_password));

  if (strlen(username) == 0 || strlen(password) == 0) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK, "Nome de usuário e senha não podem estar vazios.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return;
  }

  char filename[256];
  snprintf(filename, sizeof(filename), "vault_%s.dat", username);

  unsigned char output[8192];
  int len = load_vault(filename, password, output, sizeof(output));

  if (len > 0) {
    output[len] = '\0';

    if (load_entries((char *)output, &current_vault)) {
      snprintf(current_vault_file, sizeof(current_vault_file), "vault_%s.dat",
               username);
      strcpy(current_password, password);

      show_main_screen();
    } else {
      GtkWidget *dialog = gtk_message_dialog_new(
          GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,
          GTK_BUTTONS_OK, "Erro ao ler o conteúdo do vault.");
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
    }
  } else {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK, "❌ Senha incorreta ou vault não encontrado.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }
}
