#pragma once
#include <gtk/gtk.h>

void on_add_entry(GtkButton *button, gpointer user_data);
void on_edit_entry(GtkButton *button, gpointer user_data);
void on_delete_entry(GtkButton *button, gpointer user_data);
void on_save_vault(GtkButton *button, gpointer user_data);
void reload_vault_treeview(void);
