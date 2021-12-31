#ifndef _SERVER_H_
#define _SERVER_H_

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <glib.h>
#include <gio/gio.h>
#include "gdbus_demo_gen.h"

static GMainLoop *main_loop = NULL;
static ComGdbusDemo *skeleton = NULL;
static GDBusConnection *connection = NULL;

void init_dbus_server();
static void* start_main_loop(void*);
static void gdbus_acquired_callback(GDBusConnection*, const gchar*, gpointer);
static void gdbus_name_acquired_callback(GDBusConnection*, const gchar*, gpointer);
static void gdbus_name_lost_callback(GDBusConnection*, const gchar*, gpointer);
static gboolean receive_text(ComGdbusDemo*, GDBusMethodInvocation*, const gchar*, gpointer);

#endif
