#include "gui.h"

void clear_main_container() {
  if (main_container) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(main_container));
    for (GList *iter = children; iter != NULL; iter = iter->next) {
      gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
  }
}
