#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>
#include "gdbus_demo_gen.h"

bool complete = false;
static GMainLoop *main_loop = NULL;
static ComGdbusDemo *proxy = NULL;
static GDBusConnection *connection = NULL;

bool init_dbus_client();
static void* start_main_loop(void*);
static void method_call(const gchar*);
static gboolean receive_signal(ComGdbusDemo*, const gchar*, gpointer);

#endif
