#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int input_fd, output_fd;
    char *input_file = "input.txt";
    char *output_file = "output.txt";
    char buffer[1024];
    ssize_t bytes_read;

    // Membuka file input untuk dibaca
    input_fd = open(input_file, O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    // Membuka atau membuat file output untuk ditulis
    output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Failed to open output file");
        close(input_fd);
        exit(EXIT_FAILURE);
    }

    // Menggunakan dup2 untuk menduplikasi file descriptor output_fd ke stdout
    if (dup2(output_fd, STDOUT_FILENO) < 0) {
        perror("Failed to duplicate file descriptor");
        close(input_fd);
        close(output_fd);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Starting to copy content from %s to %s\n", input_file, output_file);

    // Membaca dari file input dan menulis ke stdout (yang telah diubah ke file output)
    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("Failed to write to output file");
            close(input_fd);
            close(output_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read < 0) {
        perror("Failed to read from input file");
    } else {
        fprintf(stderr, "Copy completed successfully.\n");
    }

    // Menutup file descriptor
    close(input_fd);
    close(output_fd);

    return 0;
}
