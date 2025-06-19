#include "gui_generator.h"
#include "generator.h"
#include "gui.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os widgets
typedef struct {
  GtkScale *scale_length;
  GtkToggleButton *check_upper;
  GtkToggleButton *check_lower;
  GtkToggleButton *check_numbers;
  GtkToggleButton *check_symbols;
  GtkSpinButton *spin_numbers;
  GtkSpinButton *spin_symbols;
  GtkEntry *entry_password;
  GtkWidget *window;
} GeneratorWidgets;

// 🎯 Função gerar senha
void on_generate_password(GtkButton *button, gpointer user_data) {
  GeneratorWidgets *widgets = (GeneratorWidgets *)user_data;

  int length = (int)gtk_range_get_value(GTK_RANGE(widgets->scale_length));
  int min_numbers = gtk_spin_button_get_value_as_int(widgets->spin_numbers);
  int min_symbols = gtk_spin_button_get_value_as_int(widgets->spin_symbols);

  gboolean use_upper = gtk_toggle_button_get_active(widgets->check_upper);
  gboolean use_lower = gtk_toggle_button_get_active(widgets->check_lower);
  gboolean use_numbers = gtk_toggle_button_get_active(widgets->check_numbers);
  gboolean use_symbols = gtk_toggle_button_get_active(widgets->check_symbols);

  if (!use_upper && !use_lower && !use_numbers && !use_symbols) {
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_password),
                       "Selecione pelo menos um tipo.");
    return;
  }

  if (min_numbers + min_symbols > length) {
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_password),
                       "Comprimento insuficiente.");
    return;
  }

  char *password = generate_password(length, use_upper, use_lower, use_numbers,
                                     use_symbols, min_numbers, min_symbols);

  if (password) {
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_password), password);
    free(password);
  } else {
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_password), "Erro na geração.");
  }
}

// 📋 Função copiar senha
void on_copy_password(GtkButton *button, gpointer user_data) {
  GeneratorWidgets *widgets = (GeneratorWidgets *)user_data;
  const gchar *text = gtk_entry_get_text(GTK_ENTRY(widgets->entry_password));

  if (strlen(text) == 0) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(widgets->window), GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK, "Nada para copiar. Gere uma senha primeiro.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return;
  }

  GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
  gtk_clipboard_set_text(clipboard, text, -1);
}

// ❌ Liberar memória ao fechar
void on_close_password_generator(GtkWidget *widget, gpointer user_data) {
  GeneratorWidgets *widgets = (GeneratorWidgets *)user_data;
  free(widgets);
}

// 🚀 Função abrir o gerador
void show_password_generator(GtkButton *button, gpointer user_data) {
  GeneratorWidgets *widgets = malloc(sizeof(GeneratorWidgets));

  widgets->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(widgets->window), "🔑 Gerador de Senha");
  gtk_window_set_default_size(GTK_WINDOW(widgets->window), 400, 450);
  gtk_window_set_position(GTK_WINDOW(widgets->window), GTK_WIN_POS_CENTER);

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
  gtk_container_add(GTK_CONTAINER(widgets->window), vbox);

  // 📏 Slider comprimento
  gtk_box_pack_start(GTK_BOX(vbox),
                     gtk_label_new("Comprimento da senha (mínimo 14):"), FALSE,
                     FALSE, 0);
  widgets->scale_length = GTK_SCALE(
      gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 14, 64, 1));
  gtk_range_set_value(GTK_RANGE(widgets->scale_length), 16);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->scale_length), FALSE,
                     FALSE, 0);

  // ✅ Checkboxes
  widgets->check_upper =
      GTK_TOGGLE_BUTTON(gtk_check_button_new_with_label("A-Z (Maiúsculas)"));
  gtk_toggle_button_set_active(widgets->check_upper, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->check_upper), FALSE,
                     FALSE, 0);

  widgets->check_lower =
      GTK_TOGGLE_BUTTON(gtk_check_button_new_with_label("a-z (Minúsculas)"));
  gtk_toggle_button_set_active(widgets->check_lower, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->check_lower), FALSE,
                     FALSE, 0);

  widgets->check_numbers =
      GTK_TOGGLE_BUTTON(gtk_check_button_new_with_label("0-9 (Números)"));
  gtk_toggle_button_set_active(widgets->check_numbers, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->check_numbers), FALSE,
                     FALSE, 0);

  widgets->check_symbols =
      GTK_TOGGLE_BUTTON(gtk_check_button_new_with_label("!@#$%^&* (Símbolos)"));
  gtk_toggle_button_set_active(widgets->check_symbols, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->check_symbols), FALSE,
                     FALSE, 0);

  // 🔢 Spin mínimos
  gtk_box_pack_start(GTK_BOX(vbox), gtk_label_new("Mínimo de números:"), FALSE,
                     FALSE, 0);
  widgets->spin_numbers =
      GTK_SPIN_BUTTON(gtk_spin_button_new_with_range(0, 64, 1));
  gtk_spin_button_set_value(widgets->spin_numbers, 1);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->spin_numbers), FALSE,
                     FALSE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), gtk_label_new("Mínimo de símbolos:"), FALSE,
                     FALSE, 0);
  widgets->spin_symbols =
      GTK_SPIN_BUTTON(gtk_spin_button_new_with_range(0, 64, 1));
  gtk_spin_button_set_value(widgets->spin_symbols, 1);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->spin_symbols), FALSE,
                     FALSE, 0);

  // 🔑 Entry da senha
  widgets->entry_password = GTK_ENTRY(gtk_entry_new());
  gtk_entry_set_max_length(widgets->entry_password, 128);
  gtk_editable_set_editable(GTK_EDITABLE(widgets->entry_password), FALSE);
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(widgets->entry_password), FALSE,
                     FALSE, 0);

  // 🎯 Botões
  GtkWidget *btn_generate = gtk_button_new_with_label("🚀 Gerar Senha");
  gtk_box_pack_start(GTK_BOX(vbox), btn_generate, FALSE, FALSE, 0);

  GtkWidget *btn_copy = gtk_button_new_with_label("📋 Copiar");
  gtk_box_pack_start(GTK_BOX(vbox), btn_copy, FALSE, FALSE, 0);

  // 🔗 Sinais
  g_signal_connect(btn_generate, "clicked", G_CALLBACK(on_generate_password),
                   widgets);
  g_signal_connect(btn_copy, "clicked", G_CALLBACK(on_copy_password), widgets);
  g_signal_connect(widgets->window, "destroy",
                   G_CALLBACK(on_close_password_generator), widgets);

  gtk_widget_show_all(widgets->window);
}
