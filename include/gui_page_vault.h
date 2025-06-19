#pragma once
#include <gtk/gtk.h>

extern GtkWidget *vault_treeview;

GtkWidget *create_vault_page();
void reload_vault_treeview(void);
