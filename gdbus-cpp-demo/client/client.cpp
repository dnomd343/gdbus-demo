#include "client.h"

// 进程主循环函数
static void* start_main_loop(void *) {
    g_main_loop_run(main_loop);
    return nullptr;
}

// 接收完成信号
static gboolean receive_signal(ComGdbusDemo *, const gchar *, gpointer) {
    complete = true;
    return true;
}

// 发送一段文字并获取返回
static void method_call(const gchar *str_send) {
    GError *error = nullptr;
    gchar *str_return = nullptr;
    g_print("Send -> %s\n", str_send);
    com_gdbus_demo_call_show_data_sync(proxy, str_send, &str_return, nullptr, &error); // 发送请求
    if (error != nullptr) { // 发送请求失败
        g_print("Failed to call method: %s.\n", error->message);
        g_error_free(error);
    }
    g_print("Return -> %s\n", str_return);
    g_free(str_return);
}

// 初始化DBus连接
bool init_dbus_client() {
    GError *proxy_error = nullptr;
    GError *connect_error = nullptr;
    connection = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, &connect_error); // 建立连接
    if (connect_error != nullptr) { // 连接失败
        g_print("Failed to connect dbus: %s.\n", connect_error->message);
        g_error_free(connect_error);
        return false;
    }
    proxy = com_gdbus_demo_proxy_new_sync(connection, G_DBUS_PROXY_FLAGS_NONE, "com.gdbus.demo",
                                          "/com/gdbus/object", nullptr, &proxy_error); // 创建Proxy
    if (proxy == nullptr) { // 创建Proxy失败
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
    main_loop= g_main_loop_new(nullptr, false); // 创建主循环对象
    g_signal_connect(proxy, "complete", G_CALLBACK(receive_signal), nullptr); // 监听信号
    pthread_create(&tid, nullptr, start_main_loop, nullptr); // 创建线程 进入主循环
    while (!complete); // 循环等待server完成
    g_print("OK\n");
    return 0;
}
