#pragma once

#include "vault.h"
#include <gtk/gtk.h>

// Containers
extern GtkWidget *main_container;
// Janelas
extern GtkWidget *window;

// Entradas
extern GtkWidget *entry_username;
extern GtkWidget *entry_password;
extern GtkWidget *entry_confirm;
extern GtkWidget *entry_login_username;
extern GtkWidget *entry_login_password;

// Dados do vault
extern VaultData current_vault;
extern GtkWidget *vault_treeview;
extern GtkListStore *vault_list_store;
extern char current_vault_file[256];
extern char current_password[256];
