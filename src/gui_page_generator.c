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
  // 🔲 Container principal para centralizar
  GtkWidget *outer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(outer_box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(outer_box, GTK_ALIGN_CENTER);

  // 🔳 Frame limitador do tamanho
  GtkWidget *frame = gtk_frame_new(NULL);
  gtk_box_pack_start(GTK_BOX(outer_box), frame, TRUE, TRUE, 20);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);

  // 🔳 VBox interno
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 16);
  gtk_container_add(GTK_CONTAINER(frame), vbox);

  // 🔒 Limita o tamanho máximo (largura x altura)
  gtk_widget_set_size_request(vbox, 600, -1);

  // 📏 Comprimento da Senha
  GtkWidget *label_length = gtk_label_new("Comprimento da Senha:");
  gtk_widget_set_halign(label_length, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(vbox), label_length, FALSE, FALSE, 0);

  scale_length = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 6, 64, 1);
  gtk_range_set_value(GTK_RANGE(scale_length), 16);
  gtk_box_pack_start(GTK_BOX(vbox), scale_length, FALSE, FALSE, 0);

  // 🔤 Frame - Caracteres Permitidos
  GtkWidget *frame_charset = gtk_frame_new("Caracteres Permitidos");
  gtk_box_pack_start(GTK_BOX(vbox), frame_charset, FALSE, FALSE, 0);

  GtkWidget *vbox_charset = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_add(GTK_CONTAINER(frame_charset), vbox_charset);

  check_upper = gtk_check_button_new_with_label("A-Z (Maiúsculas)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_upper), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox_charset), check_upper, FALSE, FALSE, 0);

  check_lower = gtk_check_button_new_with_label("a-z (Minúsculas)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_lower), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox_charset), check_lower, FALSE, FALSE, 0);

  check_numbers = gtk_check_button_new_with_label("0-9 (Números)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_numbers), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox_charset), check_numbers, FALSE, FALSE, 0);

  check_symbols = gtk_check_button_new_with_label("!@#$%^&* (Símbolos)");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_symbols), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox_charset), check_symbols, FALSE, FALSE, 0);

  // 🔢 Grid - Mínimos
  GtkWidget *grid_min = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid_min), 8);
  gtk_grid_set_column_spacing(GTK_GRID(grid_min), 12);
  gtk_box_pack_start(GTK_BOX(vbox), grid_min, FALSE, FALSE, 0);

  GtkWidget *label_min_numbers = gtk_label_new("Mínimo de números:");
  gtk_widget_set_halign(label_min_numbers, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid_min), label_min_numbers, 0, 0, 1, 1);

  spin_numbers = gtk_spin_button_new_with_range(0, 64, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_numbers), 1);
  gtk_grid_attach(GTK_GRID(grid_min), spin_numbers, 1, 0, 1, 1);

  GtkWidget *label_min_symbols = gtk_label_new("Mínimo de símbolos:");
  gtk_widget_set_halign(label_min_symbols, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid_min), label_min_symbols, 0, 1, 1, 1);

  spin_symbols = gtk_spin_button_new_with_range(0, 64, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_symbols), 1);
  gtk_grid_attach(GTK_GRID(grid_min), spin_symbols, 1, 1, 1, 1);

  // 🧠 Output - Senha
  entry_password = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry_password), 128);
  gtk_editable_set_editable(GTK_EDITABLE(entry_password), FALSE);
  gtk_box_pack_start(GTK_BOX(vbox), entry_password, FALSE, FALSE, 0);

  // 🎯 Botões
  GtkWidget *hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);

  GtkWidget *btn_generate = gtk_button_new_with_label("🚀 Gerar Senha");
  gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_generate, TRUE, TRUE, 0);

  GtkWidget *btn_copy = gtk_button_new_with_label("📋 Copiar");
  gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_copy, TRUE, TRUE, 0);

  // 🔗 Conectar sinais
  g_signal_connect(btn_generate, "clicked", G_CALLBACK(on_generate_password),
                   NULL);
  g_signal_connect(btn_copy, "clicked", G_CALLBACK(on_copy_password), NULL);

  return outer_box;
}
