#ifndef _SERVER_H_
#define _SERVER_H_

#include "gdbus_demo_gen.h"

static GMainLoop *main_loop = nullptr;
static ComGdbusDemo *skeleton = nullptr;
static GDBusConnection *connection = nullptr;

void init_dbus_server();
static void* start_main_loop(void*);
static void gdbus_acquired_callback(GDBusConnection*, const gchar*, gpointer);
static void gdbus_name_acquired_callback(GDBusConnection*, const gchar*, gpointer);
static void gdbus_name_lost_callback(GDBusConnection*, const gchar*, gpointer);
static gboolean receive_text(ComGdbusDemo*, GDBusMethodInvocation*, const gchar*, gpointer);

#endif
