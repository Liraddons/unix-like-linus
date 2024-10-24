#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "ipc/ipc.h"
#include "fs/fs.h"
#include "config/config.c"

// Функция для выполнения команд в новом потоке
void *command_thread(void *arg) {
    char *command = (char *)arg;
    char *args[10];
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    // Обработка команд
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: отсутствует аргумент\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
    } else if (strcmp(args[0], "mkdir") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "mkdir: отсутствует имя каталога\n");
        } else {
            create_directory(args[1]);
        }
    } else if (strcmp(args[0], "rmdir") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "rmdir: отсутствует имя каталога\n");
        } else {
            delete_directory(args[1]);
        }
    } else if (strcmp(args[0], "rm") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "rm: отсутствует имя файла\n");
        } else {
            delete_file(args[1]);
        }
    } else if (strcmp(args[0], "touch") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "touch: отсутствует имя файла\n");
        } else {
            create_file(args[1]);
        }
    } else if (strcmp(args[0], "ls") == 0) {
        list_files();
    } else if (strcmp(args[0], "send") == 0) {
        // Отправка сообщения через IPC
        if (args[1] == NULL) {
            fprintf(stderr, "send: отсутствует сообщение\n");
        } else {
            int msgid = create_message_queue();
            send_message(msgid, args[1]);
        }
    } else if (strcmp(args[0], "receive") == 0) {
        // Получение сообщения через IPC
        char buffer[100];
        int msgid = create_message_queue();
        receive_message(msgid, buffer);
        printf("Получено сообщение: %s\n", buffer);
    } else {
        int status = system(command);
        if (status == -1) {
            perror("Ошибка выполнения команды");
        }
    }

    return NULL;
}

void execute_command(char *command) {
    // Проверка на группировку команд
    if (strstr(command, ":")) {
        char *group = strtok(command, ":");
        char *cmds = strtok(NULL, ":");
        printf("Выполняем группу: %s\n", group);
        char *token = strtok(cmds, ";");
        while (token != NULL) {
            // Убираем пробелы в начале и конце команды
            while (*token == ' ') token++;
            execute_command(token); // Выполнение каждой команды в группе
            token = strtok(NULL, ";");
        }
    } else {
        pthread_t tid;
        // Создание потока для выполнения команды
        if (pthread_create(&tid, NULL, command_thread, strdup(command)) != 0) {
            perror("Ошибка создания потока");
        }

        // Ждем завершения потока
        pthread_join(tid, NULL);
    }
}

int main() {
    load_config(); // Загружаем конфигурацию

    char command[256];

    while (1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("my_terminal [%s]> ", cwd);
        } else {
            perror("getcwd");
            break;
        }

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(command);
    }

    return 0;
}
