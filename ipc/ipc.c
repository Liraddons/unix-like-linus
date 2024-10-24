#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

int create_message_queue() {
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

void send_message(int msgid, const char *message) {
    struct msg_buffer msg;
    msg.msg_type = 1; // Тип сообщения
    strncpy(msg.msg_text, message, sizeof(msg.msg_text) - 1);
    msg.msg_text[sizeof(msg.msg_text) - 1] = '\0';

    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
    }
}

void receive_message(int msgid, char *buffer) {
    struct msg_buffer msg;

    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
        perror("msgrcv");
    } else {
        strcpy(buffer, msg.msg_text);
    }
}
