#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key = 5678; // Kunci unik untuk shared memory

    // Membuat shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Menautkan shared memory ke ruang alamat proses
    char *shmaddr = shmat(shmid, NULL, 0);

    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Menerima input dari pengguna
    printf("Enter a string: ");
    fgets(shmaddr, SHM_SIZE, stdin);

    // Membuat child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Proses anak
        printf("Child Process: Calculating the length of the string.\n");

        // Menghitung panjang string
        int length = 0;
        while (shmaddr[length] != '\0') {
            length++;
        }

        // Menampilkan hasil
        printf("Child Process: Length of the string is %d characters.\n", length);

        // Melepaskan proses anak
        exit(EXIT_SUCCESS);
    } else {
        // Proses induk
        // Menunggu proses anak selesai
        wait(NULL);

        // Melepaskan shared memory
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        // Menghapus shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
