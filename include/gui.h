#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

void start_gui(int argc, char *argv[]);

// Criação de conta
void show_create_account_screen();
void on_create_account_confirm(GtkButton *button, gpointer user_data);
void on_back_to_home(GtkButton *button, gpointer user_data);

// Login
void show_login_screen();
void on_login_confirm(GtkButton *button, gpointer user_data);
void on_back_to_home_from_login(GtkButton *button, gpointer user_data);

// Tela inicial
void on_create_account_clicked(GtkButton *button, gpointer user_data);
void on_unlock_vault_clicked(GtkButton *button, gpointer user_data);

#endif
