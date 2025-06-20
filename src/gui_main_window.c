#include "gui.h"

GtkWidget *stack;

void show_main_screen() {
  clear_main_container();

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(main_container), vbox);

  // Stack para trocar páginas
  stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack),
                                GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
  gtk_stack_set_transition_duration(GTK_STACK(stack), 200);

  // Adiciona as páginas no stack
  GtkWidget *vault_page = create_vault_page();
  GtkWidget *generator_page = create_generator_page();
  GtkWidget *settings_page = create_settings_page();

  gtk_stack_add_named(GTK_STACK(stack), vault_page, "vault");
  gtk_stack_add_named(GTK_STACK(stack), generator_page, "generator");
  gtk_stack_add_named(GTK_STACK(stack), settings_page, "settings");

  gtk_box_pack_start(GTK_BOX(vbox), stack, TRUE, TRUE, 0);

  // Footer fixado no bottom
  GtkWidget *footer = create_footer();
  gtk_box_pack_end(GTK_BOX(vbox), footer, FALSE, FALSE, 5);

  reload_vault_treeview();
  gtk_widget_show_all(main_container);
}

void switch_page(const char *page_name) {
  gtk_stack_set_visible_child_name(GTK_STACK(stack), page_name);
}
