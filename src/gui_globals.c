#include "gui_globals.h"

// Containers
GtkWidget *main_container = NULL;

// Janelas
GtkWidget *window = NULL;

// Entradas
GtkWidget *entry_username = NULL;
GtkWidget *entry_password = NULL;
GtkWidget *entry_confirm = NULL;
GtkWidget *entry_login_username = NULL;
GtkWidget *entry_login_password = NULL;

// Dados do vault
VaultData current_vault;
GtkWidget *vault_treeview = NULL;
GtkListStore *vault_list_store = NULL;
char current_vault_file[256] = {0};
char current_password[256] = {0};
