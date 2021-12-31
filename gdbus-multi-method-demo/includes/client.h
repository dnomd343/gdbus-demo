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

static ComGdbusDemo *proxy = NULL;
static GDBusConnection *connection = NULL;

bool init_dbus_client();
static void send_text(const gchar*, gchar**, GError**);

#endif
