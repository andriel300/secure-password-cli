#include "gui.h"
#include "gui_utils.h"

void load_css() {
  GtkCssProvider *provider = gtk_css_provider_new();
  GdkDisplay *display = gdk_display_get_default();
  GdkScreen *screen = gdk_display_get_default_screen(display);

  const char *css_file = get_css_path();
  if (!css_file) {
    g_warning(
        "❌ CSS não encontrado. O aplicativo continuará sem estilização.");
    return;
  }

  gtk_css_provider_load_from_path(provider, css_file, NULL);

  gtk_style_context_add_provider_for_screen(
      screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  load_css(); // ✔️ Carregar o CSS logo após inicializar o GTK

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "🔐 Secure Password CLI");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  main_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_container);

  show_home_screen();

  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
