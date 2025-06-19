#pragma once

#include <gtk/gtk.h>

void show_login_screen(void);
void on_login_confirm(GtkButton *button, gpointer user_data);
void on_back_to_home_from_login(GtkButton *button, gpointer user_data);
