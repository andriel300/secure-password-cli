#pragma once

#include <gtk/gtk.h>

void show_main_screen(void);
void load_treeview_from_vault(void);

void on_add_entry(GtkButton *button, gpointer user_data);
void on_edit_entry(GtkButton *button, gpointer user_data);
void on_delete_entry(GtkButton *button, gpointer user_data);
void on_save_vault(GtkButton *button, gpointer user_data);
void on_logout(GtkButton *button, gpointer user_data);
