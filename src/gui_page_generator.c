#include "generator.h"
#include "gui.h"
#include "gui_globals.h"

// Widgets globais
GtkWidget *scale_length;
GtkWidget *check_upper;
GtkWidget *check_lower;
GtkWidget *check_numbers;
GtkWidget *check_symbols;
GtkWidget *spin_numbers;
GtkWidget *spin_symbols;

// 🔑 Gerar Senha
void on_generate_password(GtkButton *button, gpointer user_data) {
  int length = (int)gtk_range_get_value(GTK_RANGE(scale_length));

  gboolean use_upper =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_upper));
  gboolean use_lower =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_lower));
  gboolean use_numbers =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_numbers));
  gboolean use_symbols =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_symbols));

  int min_numbers =
      gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_numbers));
  int min_symbols =
      gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_symbols));

  // 🔥 Validação: Se checkbox desmarcado, mínimo zera
  if (!use_numbers)
    min_numbers = 0;
  if (!use_symbols)
    min_symbols = 0;

  // 🚫 Validação: Pelo menos um charset selecionado
  if (!use_upper && !use_lower && !use_numbers && !use_symbols) {
    gtk_entry_set_text(GTK_ENTRY(entry_password),
                       "❌ Nenhum charset selecionado.");
    return;
  }

  // 🚫 Validação: Comprimento suficiente
  if (length < (min_numbers + min_symbols)) {
    gtk_entry_set_text(GTK_ENTRY(entry_password),
                       "❌ Comprimento insuficiente.");
    return;
  }

  // ✅ Gerar
  char *password = generate_password(length, use_upper, use_lower, use_numbers,
                                     use_symbols, min_numbers, min_symbols);

  if (password) {
    gtk_entry_set_text(GTK_ENTRY(entry_password), password);
    free(password);
  } else {
    gtk_entry_set_text(GTK_ENTRY(entry_password), "❌ Erro ao gerar senha.");
  }
}

// 📋 Copiar senha
void on_copy_password(GtkButton *button, gpointer user_data) {
  const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry_password));

  if (strlen(text) == 0) {
    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
        "Nada para copiar. Gere uma senha primeiro.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return;
  }

  GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
  gtk_clipboard_set_text(clipboard, text, -1);
}

// 🎨 Criar página Generator
GtkWidget *create_generator_page() {
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

  // 📏 Comprimento
  GtkWidget *label_length = gtk_label_new("Comprimento da Senha:");
  gtk_box_pack_start(GTK_BOX(vbox), label_length, FALSE, FALSE, 0);

  scale_length = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 6, 64, 1);
  gtk_range_set_value(GTK_RANGE(scale_length), 16);
  gtk_box_pack_start(GTK_BOX(vbox), scale_length, FALSE, FALSE, 0);

  // ✅ Checkboxes
  check_upper = gtk_check_button_new_with_label("A-Z (Maiúsculas)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_upper), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), check_upper, FALSE, FALSE, 0);

  check_lower = gtk_check_button_new_with_label("a-z (Minúsculas)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_lower), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), check_lower, FALSE, FALSE, 0);

  check_numbers = gtk_check_button_new_with_label("0-9 (Números)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_numbers), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), check_numbers, FALSE, FALSE, 0);

  check_symbols = gtk_check_button_new_with_label("!@#$%^&* (Símbolos)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_symbols), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), check_symbols, FALSE, FALSE, 0);

  // 🔢 Mínimos
  GtkWidget *label_min_numbers = gtk_label_new("Mínimo de números:");
  gtk_box_pack_start(GTK_BOX(vbox), label_min_numbers, FALSE, FALSE, 0);

  spin_numbers = gtk_spin_button_new_with_range(0, 64, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_numbers), 1);
  gtk_box_pack_start(GTK_BOX(vbox), spin_numbers, FALSE, FALSE, 0);

  GtkWidget *label_min_symbols = gtk_label_new("Mínimo de símbolos:");
  gtk_box_pack_start(GTK_BOX(vbox), label_min_symbols, FALSE, FALSE, 0);

  spin_symbols = gtk_spin_button_new_with_range(0, 64, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_symbols), 1);
  gtk_box_pack_start(GTK_BOX(vbox), spin_symbols, FALSE, FALSE, 0);

  // 🧠 Output
  entry_password = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry_password), 128);
  gtk_editable_set_editable(GTK_EDITABLE(entry_password), FALSE);
  gtk_box_pack_start(GTK_BOX(vbox), entry_password, FALSE, FALSE, 0);

  // 🎯 Botões
  GtkWidget *btn_generate = gtk_button_new_with_label("🚀 Gerar Senha");
  gtk_box_pack_start(GTK_BOX(vbox), btn_generate, FALSE, FALSE, 0);

  GtkWidget *btn_copy = gtk_button_new_with_label("📋 Copiar");
  gtk_box_pack_start(GTK_BOX(vbox), btn_copy, FALSE, FALSE, 0);

  // 🔗 Conectar funções
  g_signal_connect(btn_generate, "clicked", G_CALLBACK(on_generate_password),
                   NULL);
  g_signal_connect(btn_copy, "clicked", G_CALLBACK(on_copy_password), NULL);

  return vbox;
}
