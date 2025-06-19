#pragma once
#include <gtk/gtk.h>

void show_password_generator(GtkButton *button, gpointer user_data);
void on_generate_password(GtkButton *button, gpointer user_data);
void on_copy_password(GtkButton *button, gpointer user_data);
