#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

// Функции для IPC
int create_message_queue();
void send_message(int msgid, const char *message);
void receive_message(int msgid, char *buffer);

#endif // IPC_H
