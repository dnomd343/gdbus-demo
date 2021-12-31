#include "server.h"

// 进程主循环函数
static void* start_main_loop(void* args) {
    g_main_loop_run(main_loop); // 进入主循环
}

// 发送信号
static gboolean send_signal(gconstpointer p) {
    com_gdbus_demo_emit_send_signal(skeleton, 233);
    g_print("Signal sent.\n");
    return true;
}

// 如果无法建立与总线的连接会调用 name_lost_handler()
// 如果无法获取 bus-name，会先调用 bus_acquired_handler()，再调用 name_lost_handler()
// 如果已获得 bus-name ，会先调用 bus_acquired_handler()，再调用 name_acquired_handler()

// GDBus Acquired 回调
static void gdbus_acquired_callback(GDBusConnection *callback_connection, const gchar *name, gpointer user_data) {
    GError *error = NULL;
    skeleton = com_gdbus_demo_skeleton_new();
    g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(skeleton), callback_connection,
                                     "/com/gdbus/object", &error); // 绑定到对象上
    if(error != 0) {
        g_print("Failed to export object: %s.\n", error->message);
        g_error_free(error);
        g_main_loop_quit(main_loop);
        return;
    }
    g_print("Skeleton load successfully.\n");
}

// GDBus Name Acquired 回调
static void gdbus_name_acquired_callback(GDBusConnection *callback_connection, const gchar *name, gpointer user_data) {
    g_print("Acquired bus-name success.\n");
}

// GDBus Name Lost 回调
static void gdbus_name_lost_callback(GDBusConnection *callback_connection, const gchar *name, gpointer user_data) {
    g_print("Name lost error: Failed to get bus-name.\n");
    g_main_loop_quit(main_loop); // 退出主循环
}

// 初始化DBus连接
void init_dbus_server() {
    main_loop = g_main_loop_new(NULL, FALSE); // 创建主循环对象
    // 申请 bus-name 并将结果给到回调函数
    g_bus_own_name(G_BUS_TYPE_SESSION, "com.gdbus.demo", G_BUS_NAME_OWNER_FLAGS_NONE,
                   &gdbus_acquired_callback, &gdbus_name_acquired_callback,
                   &gdbus_name_lost_callback, NULL, NULL);
}

int main() {
    pthread_t tid;
    init_dbus_server(); // 初始化DBus连接
    g_timeout_add(2000, (GSourceFunc)send_signal, NULL); // 定时发送信号
    pthread_create(&tid, NULL, start_main_loop, NULL); // 创建线程 进入主循环
    for (;;) {} // 死循环
}
