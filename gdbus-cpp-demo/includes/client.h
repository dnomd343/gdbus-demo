#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "gdbus_demo_gen.h"

bool complete = false;
static GMainLoop *main_loop = nullptr;
static ComGdbusDemo *proxy = nullptr;
static GDBusConnection *connection = nullptr;

bool init_dbus_client();
static void* start_main_loop(void*);
static void method_call(const gchar*);
static gboolean receive_signal(ComGdbusDemo*, const gchar*, gpointer);

#endif
