#include "client.h"

// 发送请求
static void send_text(const gchar *input_arg, gchar **output_arg, GError **error) {
    com_gdbus_demo_call_send_text_sync(proxy, input_arg, output_arg, NULL, error); // 发送请求
    if (*error != NULL) { // 发送请求失败
        g_print("Failed to call method: %s.\n", (*error)->message);
        g_error_free(*error);
    }
    g_print("Return -> %s\n", *output_arg);
    g_free(*output_arg);
}

// 初始化DBus连接
bool init_dbus_client() {
    GError *proxy_error = NULL;
    GError *connect_error = NULL;
    connection = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &connect_error); // 建立连接
    if (connect_error != NULL) { // 连接失败
        g_print("Failed to connect dbus: %s.\n", connect_error->message);
        g_error_free(connect_error);
        return false;
    }
    proxy = com_gdbus_demo_proxy_new_sync(connection, G_DBUS_PROXY_FLAGS_NONE, "com.gdbus.demo",
                                          "/com/gdbus/object", NULL, &proxy_error); // 创建Proxy
    if (proxy == 0) { // 创建Proxy失败
        g_print("Failed to create proxy: %s.\n", proxy_error->message);
        g_error_free(proxy_error);
        return false;
    }
    return true;
}

int main() {
    char str[100];
    GError *error = NULL;
    gchar *output_arg = NULL;
    if (!init_dbus_client()) { // 初始化DBus失败
        return 0;
    }
    g_print("DBus init successfully.\n"); // DBus连接成功
    for (;;) { // 死循环
        printf("> ");
        scanf("%s", str);
        send_text(str, &output_arg, &error); // 发送请求
    }
}
