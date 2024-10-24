#include <dlfcn.h>

// Пример функции для загрузки плагина
void load_plugin(const char *plugin_name) {
    void *handle = dlopen(plugin_name, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки плагина: %s\n", dlerror());
        return;
    }

    void (*init)() = dlsym(handle, "init");
    if (init) {
        init();
    }
}
