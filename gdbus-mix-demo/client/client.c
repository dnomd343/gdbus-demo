#include "client.h"

// 进程主循环函数
static void* start_main_loop(void* args) {
    g_main_loop_run(main_loop);
}

// 接收完成信号
static gboolean receive_signal(ComGdbusDemo *object, const gchar *payload, gpointer userdata) {
    complete = true;
    return true;
}

// 发送一段文字并获取返回
static void method_call(const gchar *str_send) {
    GError *error = NULL;
    gchar *str_return = NULL;
    g_print("Send -> %s\n", str_send);
    com_gdbus_demo_call_show_data_sync(proxy, str_send, &str_return, NULL, &error); // 发送请求
    if (error != NULL) { // 发送请求失败
        g_print("Failed to call method: %s.\n", error->message);
        g_error_free(error);
    }
    g_print("Return -> %s\n", str_return);
    g_free(str_return);
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

// client向server发送一段文本，server返回成功并进行处理，处理完成后发送一个信号

int main() {
    pthread_t tid;
    if (!init_dbus_client()) { // 初始化DBus失败
        return -1;
    }
    g_print("DBus init successfully.\n"); // DBus连接成功
    method_call("This is a sentence for test."); // 发送请求
    g_print("Wait for signal...");
    main_loop= g_main_loop_new(NULL, FALSE); // 创建主循环对象
    g_signal_connect(proxy, "complete", G_CALLBACK(receive_signal), NULL); // 监听信号
    pthread_create(&tid, NULL, start_main_loop, NULL); // 创建线程 进入主循环
    while (!complete); // 循环等待server完成
    g_print("OK\n");
    return 0;
}
