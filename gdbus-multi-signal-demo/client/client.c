#include "client.h"

// 进程主循环函数
static void* start_main_loop(void* args) {
    g_main_loop_run(main_loop);
}

// 接收信号1
static gboolean receive_signal_1(ComGdbusDemo *object, const gint *arg, gpointer userdata) {
	g_print("Get Signal-1: %d\n", arg);
    return true;
}

// 接收信号2
static gboolean receive_signal_2(ComGdbusDemo *object, const gdouble *arg, gpointer userdata) {
    g_print("Get Signal-2: %f\n", arg);
    return true;
}

// 接收信号3
static gboolean receive_signal_3(ComGdbusDemo *object, const gchar *arg, gpointer userdata) {
    g_print("Get Signal-3: %s\n", arg);
    return true;
}

// 初始化DBus连接
bool init_dbus_client() {
    GError *proxy_error = NULL;
    GError *connect_error = NULL;
    main_loop= g_main_loop_new(NULL,FALSE); // 创建主循环对象
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
	pthread_t tid;
    init_dbus_client(); // 初始化DBus
    g_signal_connect(proxy, "send-signal1", G_CALLBACK(receive_signal_1), NULL); // 监听信号1
    g_signal_connect(proxy, "send-signal2", G_CALLBACK(receive_signal_2), NULL); // 监听信号2
    g_signal_connect(proxy, "send-signal3", G_CALLBACK(receive_signal_3), NULL); // 监听信号3
    pthread_create(&tid, NULL, start_main_loop, NULL); // 创建线程 进入主循环
    for (;;) {} // 死循环
}
