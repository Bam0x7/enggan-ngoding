#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefds[2];
    int pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Membuat pipe
    if (pipe(pipefds) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork untuk membuat proses child
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { 
        // Proses parent

        // Menutup read-end dari pipe di parent
        close(pipefds[0]);

        // Menulis pesan ke pipe
        write(pipefds[1], write_msg, sizeof(write_msg));

        // Menutup write-end dari pipe setelah menulis
        close(pipefds[1]);

        // Menunggu proses child selesai
        wait(NULL);
    } else { 
        // Proses child

        // Menutup write-end dari pipe di child
        close(pipefds[1]);

        // Membaca pesan dari pipe
        read(pipefds[0], read_msg, sizeof(read_msg));

        // Menampilkan pesan yang diterima
        printf("Child process received: %s\n", read_msg);

        // Menutup read-end dari pipe setelah membaca
        close(pipefds[0]);
    }

    return 0;
}
