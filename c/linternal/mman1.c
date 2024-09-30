#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *file_path = "example.txt";
    int file_descriptor = open(file_path, O_RDWR | O_CREAT, (mode_t)0600);

    if (file_descriptor == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    const size_t file_size = 4096; // Ukuran file dalam byte

    // Mengatur ukuran file
    if (lseek(file_descriptor, file_size - 1, SEEK_SET) == -1) {
        close(file_descriptor);
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    // Menulis satu byte ke akhir file untuk memperluas ukurannya
    if (write(file_descriptor, "", 1) == -1) {
        close(file_descriptor);
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Memetakan file ke dalam memori
    char *mapped_data = (char *)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

    if (mapped_data == MAP_FAILED) {
        close(file_descriptor);
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Menampilkan isi file yang dipetakan
    printf("Content of the mapped file:\n%s\n", mapped_data);

    // Menutup pemetaan dan file
    if (munmap(mapped_data, file_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    close(file_descriptor);

    return 0;
}
