#include "gui.h"

GtkWidget *create_footer() {
  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_widget_set_margin_top(footer, 5);

  GtkWidget *btn_vault = gtk_button_new_with_label("🔐 Vault");
  GtkWidget *btn_generator = gtk_button_new_with_label("🛠️ Gerenciador");
  GtkWidget *btn_settings = gtk_button_new_with_label("⚙️ Configurações");

  gtk_box_pack_start(GTK_BOX(footer), btn_vault, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(footer), btn_generator, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(footer), btn_settings, TRUE, TRUE, 5);

  g_signal_connect(btn_vault, "clicked", G_CALLBACK(on_switch_to_vault), NULL);
  g_signal_connect(btn_generator, "clicked", G_CALLBACK(on_switch_to_generator),
                   NULL);
  g_signal_connect(btn_settings, "clicked", G_CALLBACK(on_switch_to_settings),
                   NULL);

  return footer;
}

void on_switch_to_vault(GtkButton *button, gpointer user_data) {
  switch_page("vault");
}

void on_switch_to_generator(GtkButton *button, gpointer user_data) {
  switch_page("generator");
}

void on_switch_to_settings(GtkButton *button, gpointer user_data) {
  switch_page("settings");
}
