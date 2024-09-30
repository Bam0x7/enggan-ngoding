#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefds[2];
    int pid;
    int numbers[] = {1, 2, 3, 4, 5}; // Array angka yang akan dikirim
    int buffer;
    int end_signal = -1;

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

        // Mengirim serangkaian angka ke child melalui pipe
        for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
            if (write(pipefds[1], &numbers[i], sizeof(numbers[i])) == -1) {
                perror("Write to pipe failed");
                exit(1);
            }
        }

        // Mengirimkan -1 sebagai sinyal akhir data
        if (write(pipefds[1], &end_signal, sizeof(end_signal)) == -1) {
            perror("Write to pipe failed");
            exit(1);
        }

        // Menutup write-end dari pipe setelah menulis
        close(pipefds[1]);

        // Menunggu proses child selesai
        wait(NULL);
    } else {
        // Proses child

        // Menutup write-end dari pipe di child
        close(pipefds[1]);

        int sum = 0;

        // Membaca data dari pipe hingga mencapai -1
        while (1) {
            if (read(pipefds[0], &buffer, sizeof(buffer)) == -1) {
                perror("Read from pipe failed");
                exit(1);
            }

            if (buffer == -1) {
                break; // Jika menemukan -1, keluar dari loop
            }

            sum += buffer;
        }

        // Menampilkan hasil perhitungan
        printf("Total sum calculated by child process: %d\n", sum);

        // Menutup read-end dari pipe setelah membaca
        close(pipefds[0]);
    }

    return 0;
}
