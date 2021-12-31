#ifndef _SERVER_H_
#define _SERVER_H_

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <gio/gio.h>
#include <glib.h>
#include "gdbus_demo_gen.h"

static GMainLoop *main_loop = NULL;
static ComGdbusDemo *skeleton = NULL;

void init_dbus_server();
static void* start_main_loop(void*);
static gboolean send_signal_1(gconstpointer);
static gboolean send_signal_2(gconstpointer);
static gboolean send_signal_3(gconstpointer);
static void gdbus_acquired_callback(GDBusConnection*, const gchar*, gpointer);
static void gdbus_name_acquired_callback(GDBusConnection*, const gchar*, gpointer);
static void gdbus_name_lost_callback(GDBusConnection*, const gchar*, gpointer);

#endif
