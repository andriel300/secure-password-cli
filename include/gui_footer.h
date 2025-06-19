#pragma once
#include <gtk/gtk.h>

GtkWidget *create_footer();

void on_switch_to_vault(GtkButton *button, gpointer user_data);
void on_switch_to_generator(GtkButton *button, gpointer user_data);
void on_switch_to_settings(GtkButton *button, gpointer user_data);
