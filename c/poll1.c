#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <sys/poll.h>
#include <pthread.h>

int main() {
    struct pollfd fds[1];
    int timeout_ms = 5000; // Waktu tunggu dalam milidetik

    // Memantau peristiwa pada stdin (file descriptor 0)
    fds[0].fd = 0; // stdin
    fds[0].events = POLLIN; // Memantau ketersediaan data untuk dibaca

    printf("Program akan menunggu input selama 5 detik...\n");

    // Memantau peristiwa dengan poll
    int result = poll(fds, 1, timeout_ms);

    if (result == -1) {
        perror("poll");
        exit(EXIT_FAILURE);
    } else if (result == 0) {
        // Tidak ada peristiwa selama waktu yang ditentukan
        printf("Waktu habis tanpa input.\n");
    } else {
        // Peristiwa terjadi pada stdin
        if (fds[0].revents & POLLIN) {
            printf("Input tersedia di stdin. Membaca...\n");

            char buffer[100];
            ssize_t bytesRead = read(0, buffer, sizeof(buffer));

            if (bytesRead == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            printf("Data yang dibaca: %.*s\n", (int)bytesRead, buffer);
        }
    }

    return 0;
}
