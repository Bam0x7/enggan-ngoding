#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>

// Struktur untuk pesan
struct Message {
    long mType;      // Tipe pesan (harus > 0)
    char mText[100]; // Isi pesan
};

int main() {
    key_t key = ftok("/tmp", 'A'); // Mendapatkan kunci unik

    // Membuat atau mendapatkan message queue
    int msgQueueID = msgget(key, 0666 | IPC_CREAT);
    if (msgQueueID == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Menginisialisasi pesan
    struct Message message;
    message.mType = 1;
    strcpy(message.mText, "Hello from Process 1!");

    // Mengirim pesan ke message queue
    if (msgsnd(msgQueueID, &message, sizeof(struct Message) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Process 1: Message sent.\n");

    // Menerima pesan dari message queue
    if (msgrcv(msgQueueID, &message, sizeof(struct Message) - sizeof(long), 2, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Process 1: Received message: %s\n", message.mText);

    // Menghapus message queue
    if (msgctl(msgQueueID, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
