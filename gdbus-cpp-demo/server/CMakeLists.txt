cmake_minimum_required(VERSION 3.16)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/includes)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/gdbus)
INCLUDE_DIRECTORIES(/usr/include/glib-2.0)
INCLUDE_DIRECTORIES(/usr/include/gio-unix-2.0)
INCLUDE_DIRECTORIES(/usr/lib/glib-2.0/include)
INCLUDE_DIRECTORIES(/usr/lib/i386-linux-gnu/glib-2.0/include)
INCLUDE_DIRECTORIES(/usr/lib/x86_64-linux-gnu/glib-2.0/include)
INCLUDE_DIRECTORIES(/usr/lib/aarch64-linux-gnu/glib-2.0/include)

add_executable(server server.cpp ${PROJECT_SOURCE_DIR}/gdbus/gdbus_demo_gen.c)
target_link_libraries(server rt pthread gio-2.0 glib-2.0 gobject-2.0 gmodule-2.0 gthread-2.0)
