#include "gui_utils.h"
#include "gui.h"
#include <limits.h> // Para PATH_MAX
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcat()
#include <sys/stat.h>
#include <unistd.h> // Para getcwd()

void clear_main_container() {
  if (main_container) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(main_container));
    for (GList *iter = children; iter != NULL; iter = iter->next) {
      gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
  }
}

// 🔍 Verifica se o arquivo existe
gboolean file_exists(const char *path) {
  struct stat buffer;
  return (stat(path, &buffer) == 0);
}

// 🔥 Função que retorna o caminho absoluto do style.css
char *get_css_path() {
  static char css_path[PATH_MAX];

  // 1️⃣ Diretório Atual
  if (getcwd(css_path, sizeof(css_path)) != NULL) {
    strcat(css_path, "/assets/style.css");
    if (file_exists(css_path)) {
      printf("✅ CSS carregado de: %s\n", css_path);
      return css_path;
    }
  }

  // 2️⃣ Diretório do Usuário
  const char *home = getenv("HOME");
  if (home != NULL) {
    snprintf(css_path, sizeof(css_path),
             "%s/.config/secure-password-cli/assets/style.css", home);
    if (file_exists(css_path)) {
      printf("✅ CSS carregado de: %s\n", css_path);
      return css_path;
    }
  }

  // 3️⃣ Diretório do Sistema
  snprintf(css_path, sizeof(css_path),
           "/usr/share/secure-password-cli/assets/style.css");
  if (file_exists(css_path)) {
    printf("✅ CSS carregado de: %s\n", css_path);
    return css_path;
  }

  // ❌ Não encontrado
  fprintf(stderr, "❌ CSS não encontrado em nenhum local padrão.\n");
  return NULL;
}
