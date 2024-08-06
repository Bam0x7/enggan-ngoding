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

    // Mendapatkan akses ke message queue yang sudah dibuat
    int msgQueueID = msgget(key, 0666);
    if (msgQueueID == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Menerima pesan dari message queue dengan tipe pesan 1
    struct Message message;
    if (msgrcv(msgQueueID, &message, sizeof(struct Message) - sizeof(long), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Process 2: Received message: %s\n", message.mText);

    // Mengganti tipe pesan untuk diirim kembali ke proses pertama
    message.mType = 2;
    strcpy(message.mText, "Hello from Process 2!");

    // Mengirim pesan kembali ke message queue
    if (msgsnd(msgQueueID, &message, sizeof(struct Message) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Process 2: Message sent back.\n");

    return 0;
}
