#include "gui.h"
#include "gui_generator.h"

void show_home_screen() {
  clear_main_container();

  GtkWidget *grid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_container_add(GTK_CONTAINER(main_container), grid);

  GtkWidget *label = gtk_label_new(
      "<span size='18000' weight='bold'>🔐 Secure Password CLI</span>");
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

  GtkWidget *subtitle = gtk_label_new("Gerencie suas senhas com segurança.");
  gtk_grid_attach(GTK_GRID(grid), subtitle, 0, 1, 2, 1);

  GtkWidget *create_btn = gtk_button_new_with_label("🆕 Criar Nova Conta");
  g_signal_connect(create_btn, "clicked",
                   G_CALLBACK(show_create_account_screen), NULL);
  gtk_grid_attach(GTK_GRID(grid), create_btn, 0, 2, 1, 1);

  GtkWidget *unlock_btn = gtk_button_new_with_label("🔐 Desbloquear Vault");
  g_signal_connect(unlock_btn, "clicked", G_CALLBACK(show_login_screen), NULL);
  gtk_grid_attach(GTK_GRID(grid), unlock_btn, 1, 2, 1, 1);

  GtkWidget *footer = gtk_label_new("© 2025 Secure Password CLI");
  gtk_grid_attach(GTK_GRID(grid), footer, 0, 3, 2, 1);

  gtk_widget_show_all(main_container);
}
