#include "gui.h"

void show_home_screen() {
  clear_main_container();

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
  gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
  gtk_container_add(GTK_CONTAINER(main_container), vbox);

  GtkWidget *label = gtk_label_new(NULL);
  gtk_label_set_markup(
      GTK_LABEL(label),
      "<span size='20000' weight='bold'>🔐 Secure Password CLI</span>");
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

  GtkWidget *subtitle = gtk_label_new("Gerencie suas senhas com segurança.");
  gtk_box_pack_start(GTK_BOX(vbox), subtitle, FALSE, FALSE, 0);

  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

  GtkWidget *create_btn = gtk_button_new_with_label("🆕 Criar Nova Conta");
  g_signal_connect(create_btn, "clicked",
                   G_CALLBACK(show_create_account_screen), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), create_btn, FALSE, FALSE, 0);

  GtkWidget *login_btn = gtk_button_new_with_label("🔐 Desbloquear Vault");
  g_signal_connect(login_btn, "clicked", G_CALLBACK(show_login_screen), NULL);
  gtk_box_pack_start(GTK_BOX(hbox), login_btn, FALSE, FALSE, 0);

  GtkWidget *footer = gtk_label_new("© 2025 Secure Password CLI");
  gtk_box_pack_end(GTK_BOX(vbox), footer, FALSE, FALSE, 0);

  gtk_widget_show_all(main_container);
}
