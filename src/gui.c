#include "gui.h"
#include "vault.h"
#include <gtk/gtk.h>

// 🔥 Variáveis globais da janela inicial
GtkWidget *window;

// 🔥 Variáveis globais da tela de criar conta
GtkWidget *window_create;
GtkWidget *entry_username;
GtkWidget *entry_password;
GtkWidget *entry_confirm;
GtkWidget *window_login;
GtkWidget *entry_login_username;
GtkWidget *entry_login_password;

// ➕ Função abrir tela de criação
void on_create_account_clicked(GtkButton *button, gpointer user_data) {
  show_create_account_screen();
}

void on_unlock_vault_clicked(GtkButton *button, gpointer user_data) {
  show_login_screen();
}

// 🏠 Função voltar pra tela inicial
void on_back_to_home(GtkButton *button, gpointer user_data) {
  gtk_widget_destroy(window_create);
  gtk_widget_show_all(window);
}

// ✔️ Função confirmar criação de conta

void on_create_account_confirm(GtkButton *button, gpointer user_data) {
  const char *username = gtk_entry_get_text(GTK_ENTRY(entry_username));
  const char *password = gtk_entry_get_text(GTK_ENTRY(entry_password));
  const char *confirm = gtk_entry_get_text(GTK_ENTRY(entry_confirm));

  if (g_strcmp0(password, confirm) != 0) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_create), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "As senhas não coincidem.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return;
  }

  if (strlen(username) == 0 || strlen(password) == 0) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_create), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
        "Nome de usuário e senha não podem estar vazios.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return;
  }

  char filename[256];
  snprintf(filename, sizeof(filename), "vault_%s.dat", username);

  if (create_vault(filename, username, password)) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_create), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Vault criado com sucesso!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  } else {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_create), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Erro ao criar o vault.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }

  gtk_widget_destroy(window_create);
  gtk_widget_show_all(window);
}

// 🆕 Tela de criação de conta
void show_create_account_screen() {
  gtk_widget_hide(window);

  window_create = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window_create), "Criar Nova Conta");
  gtk_window_set_default_size(GTK_WINDOW(window_create), 500, 300);
  gtk_window_set_position(GTK_WINDOW(window_create), GTK_WIN_POS_CENTER);
  g_signal_connect(window_create, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *grid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_container_add(GTK_CONTAINER(window_create), grid);

  GtkWidget *label = gtk_label_new(
      "<span size='18000' weight='bold'>🧑 Criar Nova Conta</span>");
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

  GtkWidget *label_user = gtk_label_new("Nome de Usuário:");
  gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);
  entry_username = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_username, 1, 1, 1, 1);

  GtkWidget *label_pass = gtk_label_new("Senha Mestre:");
  gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 2, 1, 1);
  entry_password = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
  gtk_entry_set_invisible_char(GTK_ENTRY(entry_password), '*');
  gtk_grid_attach(GTK_GRID(grid), entry_password, 1, 2, 1, 1);

  GtkWidget *label_confirm = gtk_label_new("Confirmar Senha:");
  gtk_grid_attach(GTK_GRID(grid), label_confirm, 0, 3, 1, 1);
  entry_confirm = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(entry_confirm), FALSE);
  gtk_entry_set_invisible_char(GTK_ENTRY(entry_confirm), '*');
  gtk_grid_attach(GTK_GRID(grid), entry_confirm, 1, 3, 1, 1);

  GtkWidget *create_btn = gtk_button_new_with_label("✔️ Criar Conta");
  g_signal_connect(create_btn, "clicked", G_CALLBACK(on_create_account_confirm),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), create_btn, 0, 4, 1, 1);

  GtkWidget *back_btn = gtk_button_new_with_label("⬅️ Voltar");
  g_signal_connect(back_btn, "clicked", G_CALLBACK(on_back_to_home), NULL);
  gtk_grid_attach(GTK_GRID(grid), back_btn, 1, 4, 1, 1);

  gtk_widget_show_all(window_create);
}

// 🏠 Tela inicial
void start_gui(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Secure Password CLI - GTK");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *grid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_container_add(GTK_CONTAINER(window), grid);

  GtkWidget *label = gtk_label_new(
      "<span size='18000' weight='bold'>🔐 Secure Password CLI</span>");
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

  GtkWidget *subtitle = gtk_label_new("Gerencie suas senhas com segurança.");
  gtk_grid_attach(GTK_GRID(grid), subtitle, 0, 1, 2, 1);

  GtkWidget *create_btn = gtk_button_new_with_label("🆕 Criar Nova Conta");
  g_signal_connect(create_btn, "clicked", G_CALLBACK(on_create_account_clicked),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), create_btn, 0, 2, 1, 1);

  GtkWidget *unlock_btn = gtk_button_new_with_label("🔐 Desbloquear Vault");
  g_signal_connect(unlock_btn, "clicked", G_CALLBACK(on_unlock_vault_clicked),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), unlock_btn, 1, 2, 1, 1);

  GtkWidget *footer = gtk_label_new("© 2025 Secure Password CLI");
  gtk_grid_attach(GTK_GRID(grid), footer, 0, 3, 2, 1);

  gtk_widget_show_all(window);
  gtk_main();
}

void show_login_screen() {
  gtk_widget_hide(window);

  window_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window_login), "Desbloquear Vault");
  gtk_window_set_default_size(GTK_WINDOW(window_login), 500, 250);
  gtk_window_set_position(GTK_WINDOW(window_login), GTK_WIN_POS_CENTER);
  g_signal_connect(window_login, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *grid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_container_add(GTK_CONTAINER(window_login), grid);

  GtkWidget *label = gtk_label_new(
      "<span size='18000' weight='bold'>🔐 Desbloquear Vault</span>");
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

  GtkWidget *label_user = gtk_label_new("Nome de Usuário:");
  gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);
  entry_login_username = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_login_username, 1, 1, 1, 1);

  GtkWidget *label_pass = gtk_label_new("Senha Mestre:");
  gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 2, 1, 1);
  entry_login_password = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(entry_login_password), FALSE);
  gtk_entry_set_invisible_char(GTK_ENTRY(entry_login_password), '*');
  gtk_grid_attach(GTK_GRID(grid), entry_login_password, 1, 2, 1, 1);

  GtkWidget *unlock_btn = gtk_button_new_with_label("🔓 Desbloquear Vault");
  g_signal_connect(unlock_btn, "clicked", G_CALLBACK(on_login_confirm), NULL);
  gtk_grid_attach(GTK_GRID(grid), unlock_btn, 0, 3, 1, 1);

  GtkWidget *back_btn = gtk_button_new_with_label("⬅️ Voltar");
  g_signal_connect(back_btn, "clicked", G_CALLBACK(on_back_to_home_from_login),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), back_btn, 1, 3, 1, 1);

  gtk_widget_show_all(window_login);
}

void on_back_to_home_from_login(GtkButton *button, gpointer user_data) {
  gtk_widget_destroy(window_login);
  gtk_widget_show_all(window);
}

void on_login_confirm(GtkButton *button, gpointer user_data) {
  const char *username = gtk_entry_get_text(GTK_ENTRY(entry_login_username));
  const char *password = gtk_entry_get_text(GTK_ENTRY(entry_login_password));

  if (strlen(username) == 0 || strlen(password) == 0) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_login), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
        "Nome de usuário e senha não podem estar vazios.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return;
  }

  char filename[256];
  snprintf(filename, sizeof(filename), "vault_%s.dat", username);

  unsigned char output[8192]; // Buffer para dados descriptografados
  int len = load_vault(filename, password, output, sizeof(output));

  if (len > 0) {
    output[len] = '\0'; // Garante string C

    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_login), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "✔️ Vault desbloqueado com sucesso!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    // Aqui futuramente chamamos a tela principal com as senhas
    g_print("🔓 Conteúdo do vault: %s\n", output);

    gtk_widget_destroy(window_login);
    // gtk_widget_show_all(window_main); <-- Tela principal (ainda vamos fazer)
  } else {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_login), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
        "❌ Senha incorreta ou vault não encontrado.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }
}
