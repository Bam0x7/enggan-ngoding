#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <path_to_file> <attribute_value>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];
    const char *attribute_value = argv[2];
    const char *attribute_name = "user.custom_attribute";  // Ganti dengan nama atribut yang diinginkan

    // Memasang atribut ekstended
    int result = setxattr(path, attribute_name, attribute_value, strlen(attribute_value), 0);

    if (result == 0) {
        printf("Extended attribute added successfully.\n");

        // Menampilkan daftar atribut ekstended
        char list_buffer[1024];
        ssize_t list_size = listxattr(path, list_buffer, sizeof(list_buffer));

        if (list_size > 0) {
            printf("List of extended attributes:\n");
            char *token = strtok(list_buffer, "\0");
            while (token != NULL) {
                printf("- %s\n", token);
                token = strtok(NULL, "\0");
            }
        } else if (list_size == 0) {
            printf("No extended attributes found.\n");
        } else {
            perror("listxattr");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("setxattr");
        exit(EXIT_FAILURE);
    }

    return 0;
}
