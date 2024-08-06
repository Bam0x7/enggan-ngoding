#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

const char *file_path = "example1.txt";
const size_t file_size = 4096;

// Fungsi untuk membuka file
int open_file() {
    int file_descriptor = open(file_path, O_RDWR | O_CREAT, (mode_t)0600);

    if (file_descriptor == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    return file_descriptor;
}

// Fungsi untuk mengatur ukuran file
void set_file_size(int file_descriptor) {
    if (lseek(file_descriptor, file_size - 1, SEEK_SET) == -1) {
        close(file_descriptor);
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    if (write(file_descriptor, "", 1) == -1) {
        close(file_descriptor);
        perror("write");
        exit(EXIT_FAILURE);
    }
}

// Fungsi untuk mendapatkan dan mengatur opsi file descriptor menggunakan fcntl
void configure_file_options(int file_descriptor) {
    // Mendapatkan opsi file descriptor
    int flags = fcntl(file_descriptor, F_GETFL);

    if (flags == -1) {
        close(file_descriptor);
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    printf("File descriptor options before: %x\n", flags);

    // Menambahkan opsi non-blocking
    flags |= O_NONBLOCK;

    // Mengatur kembali opsi file descriptor
    if (fcntl(file_descriptor, F_SETFL, flags) == -1) {
        close(file_descriptor);
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }

    printf("File descriptor options after: %x\n", flags);
}

// Fungsi untuk memetakan file ke dalam memori
void *map_file(int file_descriptor) {
    void *mapped_data = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

    if (mapped_data == MAP_FAILED) {
        close(file_descriptor);
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    return mapped_data;
}

// Fungsi untuk menulis ke file yang dipetakan
void write_to_mapped_file(void *mapped_data, const char *message) {
    sprintf(mapped_data, "%s", message);
}

// Fungsi untuk membaca dari file yang dipetakan
void read_from_mapped_file(void *mapped_data) {
    printf("Content of the mapped file:\n%s\n", (char *)mapped_data);
}

// Fungsi untuk melepaskan pemetaan file
void unmap_file(void *mapped_data, size_t file_size) {
    if (munmap(mapped_data, file_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
}

// Fungsi untuk menutup file
void close_file(int file_descriptor) {
    close(file_descriptor);
}

int main() {
    // Membuka file
    int file_descriptor = open_file();

    // Mengatur ukuran file
    set_file_size(file_descriptor);

    // Mendapatkan dan mengatur opsi file descriptor
    configure_file_options(file_descriptor);

    // Memetakan file ke dalam memori
    void *mapped_data = map_file(file_descriptor);

    // Menulis ke file yang dipetakan
    const char *message = "Hello, Memory Mapping!";
    write_to_mapped_file(mapped_data, message);

    // Membaca dari file yang dipetakan
    read_from_mapped_file(mapped_data);

    // Melepaskan pemetaan file
    unmap_file(mapped_data, file_size);

    // Menutup file
    close_file(file_descriptor);

    return 0;
}
