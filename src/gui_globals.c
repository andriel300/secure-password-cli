#include "gui.h"

// Janela principal e container
GtkWidget *window;
GtkWidget *main_container;

// Treeview
GtkWidget *treeview;

// Entradas
GtkWidget *entry_username;
GtkWidget *entry_password;
GtkWidget *entry_confirm;
GtkWidget *entry_login_username;
GtkWidget *entry_login_password;

// Dados do vault
VaultData current_vault;
char current_vault_file[256];
char current_password[256];
