// config.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_config() {
    FILE *file = fopen("config.txt", "r");
    if (!file) {
        perror("Не удалось открыть конфигурационный файл");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Удаление символа новой строки
        printf("Настройка: %s\n", line);
        // Здесь можно добавлять обработку каждой настройки
        // Например, если у вас есть настройка для начальной директории
        if (strncmp(line, "initial_dir=", 12) == 0) {
            char *dir = line + 12;
            chdir(dir); // Переход в указанную начальную директорию
        }
    }

    fclose(file);
}
