#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int old_fd, new_fd;
    char *file_name = "input.txt";

    // Membuka file untuk dibaca
    old_fd = open(file_name, O_RDONLY);
    if (old_fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Menduplicate file descriptor dengan nilai minimum 10
    new_fd = fcntl(old_fd, F_DUPFD, 10);
    if (new_fd < 0) {
        perror("Failed to duplicate file descriptor");
        close(old_fd);
        exit(EXIT_FAILURE);
    }

    // Menampilkan file descriptor lama dan baru
    printf("Old file descriptor: %d\n", old_fd);
    printf("New file descriptor: %d\n", new_fd);

    // Menutup file descriptor
    close(old_fd);
    close(new_fd);

    return 0;
}
