#pragma once
#include <gtk/gtk.h>

#include "gui_create_account.h"
#include "gui_footer.h"
#include "gui_globals.h"
#include "gui_home.h"
#include "gui_login.h"
#include "gui_main_window.h"
#include "gui_page_generator.h"
#include "gui_page_settings.h"
#include "gui_page_vault.h"
#include "gui_utils.h"

#include "generator.h"
#include "vault.h"

// Tela principal
void show_main_screen();
void switch_page(const char *page_name);
