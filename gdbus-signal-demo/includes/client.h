#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <gio/gio.h>
#include <glib.h>
#include "gdbus_demo_gen.h"

static ComGdbusDemo *proxy = NULL;
static GMainLoop *main_loop = NULL;
static GDBusConnection *connection = NULL;

bool init_dbus_client();
static void* start_main_loop(void*);
static gboolean receive_signal(ComGdbusDemo*, const gint*, gpointer);

#endif
